#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Engine.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>

class AsteroidComponent : public Component {
public:
    AsteroidComponent(GameObject& parent, double spawnInterval, double asteroidSpeed, double rotationSpeed)
        : Component(parent), spawnInterval(spawnInterval), asteroidSpeed(asteroidSpeed), rotationSpeed(rotationSpeed), timeSinceLastSpawn(0.0) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));  // Seed random number generator
    }

    void update() override {
        timeSinceLastSpawn += Engine::deltaTime();

        if (timeSinceLastSpawn >= spawnInterval) {
            spawnAsteroid();
            timeSinceLastSpawn = 0.0;  
        }

        // Update and check each asteroid for out-of-bounds
        for (auto it = asteroids.begin(); it != asteroids.end();) {
            auto& asteroid = *it;
            asteroid->get<BodyComponent>()->x() -= asteroidSpeed;

            // Remove asteroid if it goes off the left side of the screen
            if (asteroid->get<BodyComponent>()->x() < -128) {
                it = asteroids.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void draw() override {
        for (auto& asteroid : asteroids) {
            asteroid->draw();
        }
    }

private:
    void spawnAsteroid() {
        int yPos = (std::rand() % (Engine::height - 64));
        auto asteroid = std::make_unique<GameObject>();

        asteroid->add<BodyComponent>(Engine::width, yPos);

        asteroid->add<SpriteComponent>("asteroid", 128, 128);

        asteroids.push_back(std::move(asteroid));
    }


    double spawnInterval;       // Time interval between asteroid spawns
    double asteroidSpeed;       // Speed of asteroid movement
    double timeSinceLastSpawn;  // Time since the last asteroid spawn
    std::vector<std::unique_ptr<GameObject>> asteroids;  // Active asteroids
    double rotationSpeed;   //havent implemented this yet
};
