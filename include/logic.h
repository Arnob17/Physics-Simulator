#ifndef LOGIC_H
#define LOGIC_H

#include "objects.h"
#include <vector>
#include <memory>

class PhysicsSimulator
{
private:
    std::vector<std::unique_ptr<PhysicsObject>> objects;
    Vector2 gravity;
    float timeStep;

public:
    PhysicsSimulator(Vector2 g = {0.0f, 9.81f}, float dt = 1.0f / 60.0f);

    void addObject(std::unique_ptr<PhysicsObject> obj);
    void update();
    void draw();

    void checkCollisions();
    bool checkCircleCollision(Circle *c1, Circle *c2);
    void resolveCollision(PhysicsObject *obj1, PhysicsObject *obj2);
};

#endif // LOGIC_H
