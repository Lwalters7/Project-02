#pragma once
#include "Component.h"
#include "BodyComponent.h"

class SlideComponentX : public Component {
public:
    // Constructor
    SlideComponentX(GameObject& parent, double speed = 0.1, int leftBound = 0, int rightBound = Engine::width)
        : Component(parent), speed(speed), leftBound(leftBound), rightBound(rightBound), goingRight(true) {}

    // Update logic
    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            auto b2Body = body->getBody();
            auto position = b2Body->GetPosition().x * BodyComponent::getScale();

            // Reverse direction at bounds
            if (position >= rightBound) {
                goingRight = false;
            }
            else if (position <= leftBound) {
                goingRight = true;
            }

            // Set horizontal velocity
            b2Body->SetLinearVelocity(b2Vec2(goingRight ? speed : -speed, 0.0f)); // No vertical velocity
        }
    }

    void draw() override {}

private:
    double speed;    // Sliding speed
    bool goingRight; // Direction flag
    int leftBound;   // Left boundary for sliding
    int rightBound;  // Right boundary for sliding
};
