#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "Textures.h"
#include "Engine.h"
#include "Sounds.h"

int main(int argc, char* argv[]) {
    if (!Engine::init("SDL2 Game Engine", 900, 700)) {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();  

    Textures::load("hero", "6.png", renderer);
    Textures::load("planet1", "Terran.png", renderer);
    Textures::load("planet2", "Lava.png", renderer);
    Textures::load("planet3", "Baren.png", renderer);
    Textures::load("coin", "coin.png", renderer);
    Textures::load("diamond", "Diamond.png", renderer);
    Textures::load("blackhole", "Black_hole.png", renderer); 
    Textures::load("asteroid", "asteroid-2.png", renderer);
    Textures::load("powerUp", "coin.png", renderer);

    Sounds::load("jump", "blip.wav");
    Sounds::setVolume("jump", MIX_MAX_VOLUME / 16);
    Sounds::load("death", "cannon_x.wav");
    Sounds::setVolume("death", MIX_MAX_VOLUME / 4);
    Sounds::load("point", "chime_up.wav");
    Sounds::setVolume("point", MIX_MAX_VOLUME / 8);

    Engine::loadLevel("level.xml");

    Engine::run();

    return 0;
}
