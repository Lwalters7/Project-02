#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "Input.h"
#include "Engine.h"
#include <SDL2/SDL.h>

class ControllerComponent : public Component {
public:
    ControllerComponent(GameObject& parent)
        : Component(parent), moveSpeed(300.0), jumpForce(300.0), canJump(true) {}

    ControllerComponent(GameObject& parent, double moveSpeed, double jumpForce)
        : Component(parent), moveSpeed(moveSpeed), jumpForce(jumpForce), canJump(true) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            double movement = moveSpeed * Engine::deltaTime();
            if (Input::isKeyDown(SDLK_LEFT)) {
                body->x() -= movement;
                body->setFacingLeft(true);
            }
            if (Input::isKeyDown(SDLK_RIGHT)) {
                body->x() += movement;
                body->setFacingLeft(false);
            }

            if (Input::isKeyDown(SDLK_SPACE) && canJump) {
                body->setVelocityY(-jumpForce * Engine::deltaTime());
                canJump = false;
            }
            else if (!Input::isKeyDown(SDLK_SPACE)) {
                canJump = true;
            }
        }
    }

    void draw() override {
    }

private:
    double moveSpeed; // Movement speed in units per second
    double jumpForce; // Jump force in units per second
    bool canJump;     // Flag to check if the player can jump
};
