#pragma once
#include "Component.h"
#include "BodyComponent.h"

class GravityComponent : public Component {
public:
    GravityComponent(GameObject& parent)
        : Component(parent), gravity(1.0), terminalVelocity(10.0) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            // Apply gravity to vertical velocity
            body->velocityY() += gravity;

            // Cap at terminal velocity
            if (body->velocityY() > terminalVelocity) {
                body->velocityY() = terminalVelocity;
            }

            // Update the y-position based on velocity
            body->y() += body->velocityY();

            // Check if object has reached the ground
            if (body->y() >= groundLevel) {
                body->y() = groundLevel;           // Snap to ground level
                body->setVelocityY(0.0);           // Reset velocity on ground contact
            }
        }
    }

    void draw() override {
    }

private:
    double gravity;
    double terminalVelocity;
    const double groundLevel = 500.0; // Adjust based on screen height
};
