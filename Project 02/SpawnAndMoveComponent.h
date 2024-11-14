#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include <cstdlib>   // For random number generation
#include <ctime>     // To seed the random generator
//first attempt at spawning an object and moving and deleting, maybe can use this for bullets later.

class SpawnAndMoveComponent : public Component {
public:
    SpawnAndMoveComponent(GameObject& parent, double speed, int screenWidth, int screenHeight)
        : Component(parent), speed(speed), screenWidth(screenWidth), screenHeight(screenHeight) {
        std::srand(static_cast<unsigned>(std::time(0)));  // Seed the random number generator
        initializePosition();  // Set initial random position
    }

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            body->x() -= speed;

            // Check if the object is off the left side of the screen
            if (body->x() < 0) {
                parent().destroy();  // Call destroy to delete the object
            }
        }
    }

    void draw() override {
        // This component does not need to draw anything
    }

private:
    double speed;
    int screenWidth;
    int screenHeight;

    // Set the initial position of the object at a random y-coordinate on the right side
    void initializePosition() {
        auto body = parent().get<BodyComponent>();
        if (body) {
            body->x() = screenWidth;  // Start on the right edge of the screen
            body->y() = std::rand() % screenHeight;  // Random y-coordinate within screen bounds
        }
    }
};
