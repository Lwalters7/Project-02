#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Textures.h"
#include "View.h"

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

#include "View.h"

    void draw() override {
        auto body = parent().get<BodyComponent>();
        if (body && texture) {
            // Get the world position of the GameObject
            float worldX = body->x();
            float worldY = body->y();

            // Transform the world position to screen position using the View
            SDL_Point screenPos = View::getInstance().worldToScreen(worldX, worldY);

            SDL_Rect dst;
            dst.x = screenPos.x;
            dst.y = screenPos.y;
            dst.w = static_cast<int>(width * View::getInstance().getScale());
            dst.h = static_cast<int>(height * View::getInstance().getScale());

            // Determine the flip state based on facing direction
            SDL_RendererFlip flip = body->isFacingLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

            // Render the texture with transformations applied
            SDL_RenderCopyEx(Engine::getRenderer(), texture, nullptr, &dst, body->angle() + View::getInstance().getRotation(), nullptr, flip);
        }
    }


private:
    SDL_Texture* texture;
    int width;
    int height;
};
