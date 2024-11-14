#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "Engine.h"

class GravityComponent : public Component {
public:
    GravityComponent(GameObject& parent)
        : Component(parent), gravity(8.0), terminalVelocity(600.0) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            body->velocityY() += gravity * Engine::deltaTime();

            if (body->velocityY() > terminalVelocity) {
                body->velocityY() = terminalVelocity;
            }

            body->y() += body->velocityY() * Engine::deltaTime();

            if (body->y() >= groundLevel) {
                body->y() = groundLevel;           
                body->setVelocityY(0.0);           
            }
        }
    }

    void draw() override {
    }

private:
    double gravity;        
    double terminalVelocity; 
    const double groundLevel = 500.0; 
};
