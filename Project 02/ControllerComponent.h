#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "Input.h"  // Include the Input class for key state checks
#include <SDL2/SDL.h>

class ControllerComponent : public Component {
public:
    ControllerComponent(GameObject& parent)
        : Component(parent), moveSpeed(5.0), jumpForce(10.0), canJump(true) {}

    ControllerComponent(GameObject& parent, double moveSpeed, double jumpForce)
        : Component(parent), moveSpeed(moveSpeed), jumpForce(jumpForce), canJump(true) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            // Horizontal movement
            if (Input::isKeyDown(SDLK_LEFT)) {
                body->x() -= moveSpeed;
                body->setFacingLeft(true);
            }
            if (Input::isKeyDown(SDLK_RIGHT)) {
                body->x() += moveSpeed;
                body->setFacingLeft(false);
            }

            // Jump by setting initial upward velocity
            if (Input::isKeyDown(SDLK_SPACE) && canJump) {
                body->setVelocityY(-jumpForce);  // Apply upward velocity for jump
                canJump = false;                 // Prevents continuous jumps while holding space
            }
            else if (!Input::isKeyDown(SDLK_SPACE)) {
                canJump = true;                  // Reset jump ability on release
            }
        }
    }

    void draw() override {
        // ControllerComponent does not need to draw anything
    }

private:
    double moveSpeed;
    double jumpForce;
    bool canJump;
};
