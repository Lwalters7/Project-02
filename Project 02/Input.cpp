#include "Input.h"

// Definition of static members
std::set<SDL_Keycode> Input::keysDown;
std::set<Uint8> Input::mouseButtonsDown;
std::pair<int, int> Input::mousePosition = { 0, 0 };
