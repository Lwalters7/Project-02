#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <set>
#include <utility>  // for std::pair

class Input {
public:
    // Update the input state based on SDL events (static method)
    static void processEvent(const SDL_Event& event) {
        switch (event.type) {
        case SDL_KEYDOWN:
            keysDown.insert(event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            keysDown.erase(event.key.keysym.sym);
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseButtonsDown.insert(event.button.button);
            break;

        case SDL_MOUSEBUTTONUP:
            mouseButtonsDown.erase(event.button.button);
            break;

        case SDL_MOUSEMOTION:
            mousePosition = { event.motion.x, event.motion.y };
            break;
        }
    }

    // Check if a specific key is currently down (static method)
    static bool isKeyDown(SDL_Keycode key) {
        return keysDown.find(key) != keysDown.end();
    }

    // Check if a specific mouse button is currently down (static method)
    static bool isMouseButtonDown(Uint8 button) {
        return mouseButtonsDown.find(button) != mouseButtonsDown.end();
    }

    // Get the current mouse position (static method)
    static std::pair<int, int> getMousePosition() {
        return mousePosition;
    }

private:
    static std::set<SDL_Keycode> keysDown;               // Track which keys are down (static)
    static std::set<Uint8> mouseButtonsDown;             // Track which mouse buttons are down (static)
    static std::pair<int, int> mousePosition;            // Store the current mouse position (static)
};
