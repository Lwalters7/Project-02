#pragma once
#include "Component.h"
#include "Engine.h"
#include "BodyComponent.h"
#include <cstdlib>
#include <iostream>
#include <box2d/box2d.h>
#include "Engine.h"

class AsteroidComponent : public Component {
public:
    AsteroidComponent(GameObject& parent, double speed, int level)
        : Component(parent), speed(speed), level(level) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG
    }
    
    void update() override {
        auto body = parent().get<BodyComponent>();
        auto b2Body = body->getBody();

        if (Engine::getPoints()>level) {
            if (b2Body->GetLinearVelocity().x == 0) {
                b2Vec2 velocity(-static_cast<float>(speed), 0.0f);
                b2Body->SetLinearVelocity(velocity);
            }
            if (b2Body->GetPosition().x * BodyComponent::getScale() < 0) {
                resetAsteroid(b2Body);
            }
        }
    }
    void draw() override {}

private:
    double speed;
    int level;
    bool spawn = false;

    void resetAsteroid(b2Body* b2Body) {
        float randomY = static_cast<float>(std::rand() % Engine::height);
        b2Body->SetTransform(b2Vec2(1000 / BodyComponent::getScale() , 
            randomY / BodyComponent::getScale()), b2Body->GetAngle());
        b2Vec2 velocity(-static_cast<float>(speed), 0.0f);
        b2Body->SetLinearVelocity(velocity);
    }
};