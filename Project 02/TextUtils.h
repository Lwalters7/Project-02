#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Function to render text and return it as a texture
SDL_Texture* renderText(const std::string& text, SDL_Color color, SDL_Renderer* renderer, TTF_Font* font);
