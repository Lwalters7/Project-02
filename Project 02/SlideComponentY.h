#pragma once
#include "Component.h"
#include "BodyComponent.h"

class SlideComponentY : public Component {
public:
    SlideComponentY(GameObject& parent, double speed = 0.1, int topBound = 0, int bottomBound = Engine::height)
        : Component(parent), speed(speed), topBound(topBound), bottomBound(bottomBound), goingDown(true) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            auto b2Body = body->getBody();
            auto position = b2Body->GetPosition().y * BodyComponent::getScale();

            if (position >= bottomBound) {
                goingDown = false;
            }
            else if (position <= topBound) {
                goingDown = true;
            }

            // Set the vertical velocity based on direction
            b2Body->SetLinearVelocity(b2Vec2(b2Body->GetLinearVelocity().x, goingDown ? speed : -speed));
        }
    }

    void draw() override {
        // SlideComponentY does not need to draw anything.
    }

private:
    double speed;       // Speed of vertical movement
    bool goingDown;     // Direction of movement
    int topBound;       // Top boundary
    int bottomBound;    // Bottom boundary
};
