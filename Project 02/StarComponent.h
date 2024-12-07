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
    // Constructor
    StarComponent(GameObject& parent)
        : Component(parent) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG
    }

    // Update method called every frame
    void update() override {
        auto body = parent().get<BodyComponent>();
        if (!body || !Engine::player) {
            return; // Exit if the BodyComponent or player is unavailable
        }

        auto b2Body = body->getBody();

        // Define the AABB of the star
        b2AABB starAABB;
        for (b2Fixture* f = b2Body->GetFixtureList(); f; f = f->GetNext()) {
            starAABB = f->GetAABB(0); // Get the AABB for the first fixture
            break;
        }

        // Get the player's body
        auto playerBody = Engine::player->get<BodyComponent>()->getBody();
        if (!playerBody) {
            return; // Exit if the player's BodyComponent is unavailable
        }

        // Define the AABB of the player
        b2AABB playerAABB;
        for (b2Fixture* f = playerBody->GetFixtureList(); f; f = f->GetNext()) {
            playerAABB = f->GetAABB(0); // Get the AABB for the first fixture
            break;
        }

        // Check if the player's body intersects the star's AABB
        if (b2TestOverlap(starAABB, playerAABB)) {
            moveToRandomPosition(b2Body); // Move the star to a random position
            Sounds::play("point");
        }
    }


    void draw() override {}

private:

    // Moves the star to a random position
    void moveToRandomPosition(b2Body* b2Body) {
        Engine::addPoints(1);
        std::cout << Engine::getPoints();
        float randomX = static_cast<float>(std::rand() % Engine::width);
        float randomY = static_cast<float>(std::rand() % Engine::height);

        b2Body->SetTransform(b2Vec2(randomX / BodyComponent::getScale(), randomY / BodyComponent::getScale()), b2Body->GetAngle());
    }
};
