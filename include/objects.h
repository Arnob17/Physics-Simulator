#ifndef OBJECTS_H
#define OBJECTS_H

#include <raylib.h>

class PhysicsObject
{
protected:
    Vector2 position;
    Vector2 velocity;
    float mass;
    Color color;

public:
    PhysicsObject(Vector2 pos, Vector2 vel, float m, Color c);
    virtual ~PhysicsObject() = default;

    void updatePosition(float deltaTime);
    void applyForce(Vector2 force);

    // Returns true if object is immovable (mass <= 0)
    bool isStatic() const { return mass <= 0.0f; }

    Vector2 getPosition() const { return position; }
    Vector2 getVelocity() const { return velocity; }
    float getMass() const { return mass; }

    virtual void draw() = 0;
};

class Circle : public PhysicsObject
{
private:
    float radius;

public:
    Circle(Vector2 pos, Vector2 vel, float m, float r, Color c);
    void draw() override;
    float getRadius() const { return radius; }
};

class PhysicsRectangle : public PhysicsObject
{
private:
    float width;
    float height;

public:
    PhysicsRectangle(Vector2 pos, Vector2 vel, float m, float w, float h, Color c);
    void draw() override;
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};

class floorPhysicsRectangle : public PhysicsObject
{
private:
    float width;
    float height;
public:
    floorPhysicsRectangle(Vector2 pos, Vector2 vel, float m, float w, float h, Color c);
    void draw() override;
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};

#endif // OBJECTS_H
