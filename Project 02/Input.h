#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <set>
#include <utility> 

class Input {
public:
    static void processEvent(const SDL_Event& event) {
        switch (event.type) {
        case SDL_KEYDOWN:
            keysDown.insert(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            keysDown.erase(event.key.keysym.sym);
            break;
        }
    }
    static bool isKeyDown(SDL_Keycode key) {
        return keysDown.find(key) != keysDown.end();
    }
private:
    static std::set<SDL_Keycode> keysDown;
};
