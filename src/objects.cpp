#include "../include/objects.h"

PhysicsObject::PhysicsObject(Vector2 pos, Vector2 vel, float m, Color c)
    : position(pos), velocity(vel), mass(m), color(c) {}

void PhysicsObject::updatePosition(float deltaTime)
{
    // Do not move static (immovable) objects
    if (mass <= 0.0f) return;

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void PhysicsObject::applyForce(Vector2 force)
{
    // Applying a force to an immovable object should do nothing
    if (mass <= 0.0f) return;

    velocity.x += force.x / mass;
    velocity.y += force.y / mass;
}

Circle::Circle(Vector2 pos, Vector2 vel, float m, float r, Color c)
    : PhysicsObject(pos, vel, m, c), radius(r) {}

void Circle::draw()
{
    DrawCircleV(position, radius, color);
}

PhysicsRectangle::PhysicsRectangle(Vector2 pos, Vector2 vel, float m, float w, float h, Color c)
    : PhysicsObject(pos, vel, m, c), width(w), height(h) {}

void PhysicsRectangle::draw()
{
    DrawRectangle(
        position.x - width / 2,
        position.y - height / 2,
        width, height,
        color);
}

floorPhysicsRectangle::floorPhysicsRectangle(Vector2 pos, Vector2 vel, float m, float w, float h, Color c)
    : PhysicsObject(pos, vel, m, c), width(w), height(h) {}
void floorPhysicsRectangle::draw()
{
    // Use center-based drawing like other objects (position is the center)
    DrawRectangle(
        (int)(position.x - width/2),
        (int)(position.y - height/2),
        (int)width,
        (int)height,
        color);
}

    