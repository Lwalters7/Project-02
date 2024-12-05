#pragma once
#include "Component.h"
#include <Box2D/Box2D.h>

class BodyComponent : public Component {
public:
    // Constructor to initialize the Box2D body
    BodyComponent(GameObject& owner, b2World& world, float x, float y, float width, float height, b2BodyType bodyType = b2_dynamicBody)
        : Component(owner), world(world) {
        // Define the body
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position.Set((x) / SCALE, (y) / SCALE);
        body = world.CreateBody(&bodyDef);

        // Define the shape (adjust for collision zone)
        b2PolygonShape boxShape;
        boxShape.SetAsBox((width / SCALE), (height / SCALE));

        // Define the fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);
    }


    // Access the Box2D body
    b2Body* getBody() { return body; }

    // Set position manually (useful for initializing or teleporting objects)
    void setPosition(float x, float y) {
        body->SetTransform(b2Vec2(x / SCALE, y / SCALE), body->GetAngle());
    }

    // Get position in pixels
    void getPosition(float& x, float& y) const {
        const auto& pos = body->GetPosition();
        x = pos.x * SCALE;
        y = pos.y * SCALE;
    }


    // Get linear velocity in pixels per second
    void getVelocity(float& vx, float& vy) const {
        const auto& vel = body->GetLinearVelocity();
        vx = vel.x * SCALE;
        vy = vel.y * SCALE;
    }

    // Synchronize the GameObject position with the Box2D body position
    void update() override {
        const auto& pos = body->GetPosition();
        parent().setPosition(pos.x * SCALE, pos.y * SCALE); // Convert meters back to pixels
    }

    void draw() override {
    }

    // Destructor to clean up the Box2D body
    ~BodyComponent() {
        if (body) {
            world.DestroyBody(body); // Cleanup Box2D body
            body = nullptr;
        }
    }

    // Static getter for SCALE
    static float getScale() { return SCALE; }

private:
    static constexpr float SCALE = 30.0f; // Pixels-to-meters conversion factor
    b2World& world;  // Reference to the Box2D world
    b2Body* body;    // Box2D body managed by this component
};
