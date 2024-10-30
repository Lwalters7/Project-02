#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "Textures.h"

int main(int argc, char* argv[]) {
    // Initialize the engine
    if (!Engine::init("SDL2 Game Engine", 800, 600)) {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();  // Assuming Engine provides a getRenderer method

    // Load textures into the texture manager
    Textures::load("hero", "squirrel.png", renderer);
    Textures::load("enemy", "cat.png", renderer);
    Textures::load("asteroid", "squirrel.png", renderer);

  //  auto asteroidManager = std::make_unique<GameObject>();
  //  asteroidManager->add<AsteroidComponent>(2.0, 5.0);

    // Load level from XML file
    Engine::loadLevel("level.xml");
  //  Engine::addGameObject(std::move(asteroidManager));

    // Run the engine
    Engine::run();

    return 0;
}
