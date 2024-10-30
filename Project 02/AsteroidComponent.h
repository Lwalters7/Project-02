#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Engine.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include <SDL2/SDL.h>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

class AsteroidComponent : public Component {
public:
    AsteroidComponent(GameObject& parent, double spawnInterval, double asteroidSpeed)
        : Component(parent), spawnInterval(spawnInterval), asteroidSpeed(asteroidSpeed), timeSinceLastSpawn(0.0) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));  // Seed random number generator
    }

    void update() override {
        timeSinceLastSpawn += Engine::deltaTime();

        // Spawn a new asteroid if the interval has passed
        if (timeSinceLastSpawn >= spawnInterval) {
            spawnAsteroid();
            timeSinceLastSpawn = 0.0;  // Reset the timer
        }

        // Update and check each asteroid for out-of-bounds
        for (auto it = asteroids.begin(); it != asteroids.end();) {
            auto& asteroid = *it;
            asteroid->get<BodyComponent>()->x() -= asteroidSpeed;

            // Remove asteroid if it goes off the left side of the screen
            if (asteroid->get<BodyComponent>()->x() < -64) {  // Assuming 64 is the width of the asteroid
                it = asteroids.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void draw() override {
        // Draw each asteroid (handled by its own SpriteComponent)
        for (auto& asteroid : asteroids) {
            asteroid->draw();
        }
    }

private:
    void spawnAsteroid() {
        int yPos = (std::rand() % (Engine::height - 64)) + 32;
        auto asteroid = std::make_unique<GameObject>();

        asteroid->add<BodyComponent>(Engine::width, yPos);

        // Specify custom dimensions for larger asteroids, e.g., 128x128
        asteroid->add<SpriteComponent>("asteroid", 128, 128);  // Adjust dimensions as desired

        asteroids.push_back(std::move(asteroid));
    }


    double spawnInterval;       // Time interval between asteroid spawns
    double asteroidSpeed;       // Speed of asteroid movement
    double timeSinceLastSpawn;  // Time since the last asteroid spawn
    std::vector<std::unique_ptr<GameObject>> asteroids;  // Active asteroids
};