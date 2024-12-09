#pragma once
#include "Component.h"
#include "Engine.h"
#include "BodyComponent.h"
#include <cstdlib>
#include <iostream>
#include <box2d/box2d.h>
#include "Engine.h"
#include "Sounds.h"

class StarComponent : public Component {
public:
    StarComponent(GameObject& parent)
        : Component(parent) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void update() override {
        auto body = parent().get<BodyComponent>();
        if (!body || !Engine::player) {
            return; 
        }
        auto b2Body = body->getBody();
        b2AABB starAABB;
        for (b2Fixture* f = b2Body->GetFixtureList(); f; f = f->GetNext()) {
            starAABB = f->GetAABB(0); 
            break;
        }
        auto playerBody = Engine::player->get<BodyComponent>()->getBody();
        if (!playerBody) {
            return;
        }
        b2AABB playerAABB;
        for (b2Fixture* f = playerBody->GetFixtureList(); f; f = f->GetNext()) {
            playerAABB = f->GetAABB(0); 
            break;
        }
        if (b2TestOverlap(starAABB, playerAABB)) {
            moveToRandomPosition(b2Body);
            Sounds::play("point");
        }
    }

    void draw() override {}

private:
    void moveToRandomPosition(b2Body* b2Body) {
        Engine::addPoints(1);
        std::cout << Engine::getPoints();
        float randomX = static_cast<float>(std::rand() % Engine::width);
        float randomY = static_cast<float>(std::rand() % Engine::height);

        b2Body->SetTransform(b2Vec2(randomX / BodyComponent::getScale(), 
            randomY / BodyComponent::getScale()), b2Body->GetAngle());
    }
};
