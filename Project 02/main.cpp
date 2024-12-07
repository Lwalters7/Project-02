#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "Textures.h"
#include "Engine.h"
#include "Sounds.h"

int main(int argc, char* argv[]) {
    // Initialize the engine
    if (!Engine::init("SDL2 Game Engine", 900, 700)) {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();  // Assuming Engine provides a getRenderer method

    // Load textures into the texture manager
    Textures::load("hero", "6.png", renderer);
    Textures::load("enemy", "cat.png", renderer);
    Textures::load("planet1", "Terran.png", renderer);
    Textures::load("planet2", "Lava.png", renderer);
    Textures::load("coin", "coin.png", renderer);
    Textures::load("diamond", "Diamond.png", renderer);
    Textures::load("blackhole", "Black_hole.png", renderer); \

    Sounds::load("jump", "blip.wav");
    Sounds::setVolume("jump", MIX_MAX_VOLUME / 16);
    Sounds::load("death", "cannon_x.wav");
    Sounds::setVolume("death", MIX_MAX_VOLUME / 4);

    // Load level from XML file
    Engine::loadLevel("level.xml");

    // Run the engine
    Engine::run();

    return 0;
}
