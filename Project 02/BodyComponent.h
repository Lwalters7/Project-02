#pragma once
#include "Component.h"
#include <Box2D/Box2D.h>

class BodyComponent : public Component {
public:
    BodyComponent(GameObject& owner, b2World& world, float x, float y, float width, 
        float height, b2BodyType bodyType = b2_dynamicBody)
        : Component(owner), world(world) {

        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position.Set((x) / SCALE, (y) / SCALE);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape boxShape;
        boxShape.SetAsBox((width / SCALE), (height / SCALE));

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);
    }


    b2Body* getBody() { return body; }

    void setPosition(float x, float y) {
        body->SetTransform(b2Vec2(x / SCALE, y / SCALE), body->GetAngle());
    }

    void getPosition(float& x, float& y) const {
        const auto& pos = body->GetPosition();
        x = pos.x * SCALE;
        y = pos.y * SCALE;
    }
    void getVelocity(float& vx, float& vy) const {
        const auto& vel = body->GetLinearVelocity();
        vx = vel.x * SCALE;
        vy = vel.y * SCALE;
    }

    void update() override {
        const auto& pos = body->GetPosition();
        parent().setPosition(pos.x * SCALE, pos.y * SCALE); 
    }

    void draw() override {
    }

    ~BodyComponent() {
        if (body) {
            world.DestroyBody(body); 
            body = nullptr;
        }
    }
    static float getScale() { return SCALE; }

private:
    static constexpr float SCALE = 30.0f; 
    b2World& world;  
    b2Body* body;   
};
