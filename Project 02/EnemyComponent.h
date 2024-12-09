#pragma once
#include "Component.h"
#include "Engine.h"
#include "BodyComponent.h"
#include <cstdlib>
#include <iostream>
#include <box2d/box2d.h>

class EnemyComponent : public Component {
public:
    // Constructor
    EnemyComponent(GameObject& parent, int speed = 1)
        : Component(parent), speed(speed) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        auto b2Body = body->getBody();
        auto playerBody = Engine::player->get<BodyComponent>()->getBody();

        b2Vec2 enemyPosition = b2Body->GetPosition();
        b2Vec2 playerPosition = playerBody->GetPosition();

        b2Vec2 direction = playerPosition - enemyPosition;
        direction.Normalize();

        b2Vec2 velocity = b2Vec2(direction.x * speed, direction.y * speed);
        b2Body->SetLinearVelocity(velocity); 
    }

    void draw() override {}

private:
    int speed; 
};
