#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Textures.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(GameObject& parent, const std::string& textureKey, int width = 64, int height = 64)
        : Component(parent), texture(nullptr), width(width), height(height) {
        texture = Textures::get(textureKey);
        if (!texture) {
            SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
        }
    }

    void update() override {}

    void draw() override {
        auto body = parent().get<BodyComponent>();
        if (body && texture) {
            SDL_Rect dst;
            dst.x = static_cast<int>(body->x());
            dst.y = static_cast<int>(body->y());
            dst.w = width;  // Set the desired width
            dst.h = height;  // Set the desired height

            // Determine the flip state based on facing direction
            SDL_RendererFlip flip = body->isFacingLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

            // Render the texture with the appropriate flip
            SDL_RenderCopyEx(Engine::getRenderer(), texture, nullptr, &dst, body->angle(), nullptr, flip);
        }
    }

private:
    SDL_Texture* texture;
    int width;
    int height;
};
