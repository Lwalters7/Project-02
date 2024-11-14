#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "Textures.h"

int main(int argc, char* argv[]) {
    if (!Engine::init("SDL2 Game Engine", 1000, 800)) {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();  

    Textures::load("hero", "6.png", renderer);
    Textures::load("enemy", "cat.png", renderer);
    Textures::load("asteroid", "Baren.png", renderer);
    Textures::load("planet1", "Terran.png", renderer);
    Textures::load("planet2", "Lava.png", renderer);


    Engine::loadLevel("level.xml");

    Engine::run();

    return 0;
}
