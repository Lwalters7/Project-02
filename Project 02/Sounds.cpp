#include "Sounds.h"

// Definition of static member
std::unordered_map<std::string, std::unique_ptr<Mix_Chunk, Sounds::SDL_Deleter>> Sounds::sounds;
