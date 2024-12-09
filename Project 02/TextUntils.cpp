#include "TextUtils.h"

SDL_Texture* renderText(const std::string& text, SDL_Color color, SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        SDL_Log("Failed to create text surface: %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
    }

    return texture;
}
