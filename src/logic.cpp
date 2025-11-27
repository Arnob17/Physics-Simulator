#include "../include/logic.h"
#include <cmath>

PhysicsSimulator::PhysicsSimulator(Vector2 g, float dt)
    : gravity(g), timeStep(dt) {}

void PhysicsSimulator::addObject(std::unique_ptr<PhysicsObject> obj)
{
    objects.push_back(std::move(obj));
}


//here the surface will be written

void PhysicsSimulator::update()
{
    for (auto &obj : objects)
    {
        // Apply gravity
        obj->applyForce(gravity);

        // Update position
        obj->updatePosition(timeStep);

        // Basic boundary checking (keep objects in screen)
        Vector2 pos = obj->getPosition();
        Vector2 vel = obj->getVelocity();

        if (pos.y > GetScreenHeight())
        {
            pos.y = GetScreenHeight();
            vel.y = -vel.y * 0.8f; // Bounce with energy loss
            obj->applyForce({-vel.x, -vel.y});
        }

        if (pos.x < 0 || pos.x > GetScreenWidth())
        {
            vel.x = -vel.x * 0.8f;
            obj->applyForce({-vel.x * 2, 0});
        }
    }

    checkCollisions();
}

void PhysicsSimulator::draw()
{
    for (const auto &obj : objects)
    {
        obj->draw();
    }
}

bool PhysicsSimulator::checkCircleCollision(Circle *c1, Circle *c2)
{
    Vector2 pos1 = c1->getPosition();
    Vector2 pos2 = c2->getPosition();

    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    return distance < (c1->getRadius() + c2->getRadius());
}

void PhysicsSimulator::checkCollisions()
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        for (size_t j = i + 1; j < objects.size(); j++)
        {
            auto *obj1 = objects[i].get();
            auto *obj2 = objects[j].get();

            // For now, only handle circle-circle collisions
            auto *circle1 = dynamic_cast<Circle *>(obj1);
            auto *circle2 = dynamic_cast<Circle *>(obj2);

            if (circle1 && circle2 && checkCircleCollision(circle1, circle2))
            {
                resolveCollision(obj1, obj2);
            }
        }
    }
}

void PhysicsSimulator::resolveCollision(PhysicsObject *obj1, PhysicsObject *obj2)
{
    Vector2 normal = {
        obj2->getPosition().x - obj1->getPosition().x,
        obj2->getPosition().y - obj1->getPosition().y};

    float magnitude = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    normal.x /= magnitude;
    normal.y /= magnitude;

    Vector2 relativeVelocity = {
        obj2->getVelocity().x - obj1->getVelocity().x,
        obj2->getVelocity().y - obj1->getVelocity().y};

    float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

    // If objects are moving apart, don't resolve collision
    if (velocityAlongNormal > 0)
        return;

    float restitution = 0.8f;
    float invMass1 = (obj1->getMass() <= 0.0f) ? 0.0f : 1.0f / obj1->getMass();
    float invMass2 = (obj2->getMass() <= 0.0f) ? 0.0f : 1.0f / obj2->getMass();
    float denom = invMass1 + invMass2;
    if (denom == 0.0f) return; // both objects immovable

    float j = -(1 + restitution) * velocityAlongNormal;
    j /= denom;

    Vector2 impulse = {j * normal.x, j * normal.y};

    // Apply impulse only to movable objects
    if (invMass1 > 0.0f) obj1->applyForce({-impulse.x, -impulse.y});
    if (invMass2 > 0.0f) obj2->applyForce(impulse);
}
