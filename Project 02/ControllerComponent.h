#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "Input.h"
#include <SDL2/SDL.h>
#include <algorithm>

class ControllerComponent : public Component {
public:
    ControllerComponent(GameObject& parent, double moveSpeed = 3.0, double jumpForce = 4.0)
        : Component(parent), moveSpeed(moveSpeed), jumpForce(jumpForce), canJump(true) {}

    void update() override {
        auto body = parent().get<BodyComponent>();
        auto sprite = parent().get<SpriteComponent>();

        if (body) {
            auto b2Body = body->getBody();

            if (Input::isKeyDown(SDLK_LEFT)) {
                b2Body->SetLinearVelocity(b2Vec2(-moveSpeed, b2Body->GetLinearVelocity().y));
                if (sprite) {
                    sprite->setFlip(SDL_FLIP_HORIZONTAL); // Flip texture for left movement
                }
            }
            if (Input::isKeyDown(SDLK_RIGHT)) {
                b2Body->SetLinearVelocity(b2Vec2(moveSpeed, b2Body->GetLinearVelocity().y));
                if (sprite) {
                    sprite->setFlip(SDL_FLIP_NONE); // No flip for right movement
                }
            }

            float maxJumpVelocity = -5.0f;

            if (Input::isKeyDown(SDLK_SPACE) && canJump) {
                b2Body->ApplyLinearImpulseToCenter(b2Vec2(0, -jumpForce), true);
                canJump = false;

                // Cap the vertical velocity
                b2Vec2 velocity = b2Body->GetLinearVelocity();
                float maxUpwardVelocity = -6.0f; // Maximum allowed upward velocity (negative because up is negative Y)

                if (velocity.y < maxUpwardVelocity) {
                    velocity.y = maxUpwardVelocity; // Cap the upward velocity
                    b2Body->SetLinearVelocity(velocity);
                }
            }

            if (!Input::isKeyDown(SDLK_SPACE)) {
                canJump = true;
            }

            float yVelocity = b2Body->GetLinearVelocity().y;
            float xVelocity = b2Body->GetLinearVelocity().x;
            float angularVelocity = calculateAngularVelocity(yVelocity);
            b2Body->SetAngularVelocity(angularVelocity);

            if (sprite) {
                float angle = b2Body->GetAngle() * (180.0f / M_PI); // Convert radians to degrees
                
                if (xVelocity < 0) { // Moving left
                    angle = -angle;
                }
                sprite->setAngle(angle);
            }

        }
    }

    void draw() override {}

private:
    double moveSpeed;
    double jumpForce;
    bool canJump;

    float calculateAngularVelocity(float yVelocity){
        float sensitivity = 0.1f;
        return yVelocity * sensitivity;
    }
};
