#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include <cstdlib>
#include <ctime>
#include <memory>
#include "Engine.h"

class PowerUpComponent : public Component {
public:
    PowerUpComponent(GameObject& parent, b2World& world)
        : Component(parent), world(world) {
        if (instanceExists) {
            throw std::runtime_error("Only one PowerUpComponent can be created.");
        }
        instanceExists = true; 
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }
    ~PowerUpComponent() {
        instanceExists = false;
    }
    void update() override {
        if (shouldSpawnPowerUp()) {
           // spawnPowerUp();
           // SDL_Log("Spawn coin");
           // std::cout << instanceExists;
        }
    }
    void draw() override {}
private:
    b2World& world;   
    bool instanceExists = false;

    bool shouldSpawnPowerUp() {
      if(Engine::getPoints()>0)  return true;
      return false;
    }
    void spawnPowerUp() {
        auto powerUp = std::make_unique<GameObject>();
        float x = static_cast<float>(std::rand() % Engine::width);
        float y = static_cast<float>(std::rand() % Engine::height);
        powerUp->add<BodyComponent>(world, x, y, 4, 4, b2_staticBody);
        powerUp->add<SpriteComponent>("powerUp", 4, 4); 
        gameObjects.push_back(std::move(powerUp));
    }

    std::vector<std::unique_ptr<GameObject>> gameObjects; 
};
