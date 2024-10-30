#include "Textures.h"

// Definition of static member
std::unordered_map<std::string, std::unique_ptr<SDL_Texture, Textures::SDL_Deleter>> Textures::textures;
