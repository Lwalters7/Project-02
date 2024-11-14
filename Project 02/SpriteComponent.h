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
            float worldX = body->x();
            float worldY = body->y();

            SDL_Point screenPos = View::getInstance().worldToScreen(worldX, worldY);

            SDL_Rect dst;
            dst.x = screenPos.x;
            dst.y = screenPos.y;
            dst.w = static_cast<int>(width * View::getInstance().getScale());
            dst.h = static_cast<int>(height * View::getInstance().getScale());

            SDL_RendererFlip flip = body->isFacingLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

            SDL_RenderCopyEx(Engine::getRenderer(), texture, nullptr, &dst, body->angle() + View::getInstance().getRotation(), nullptr, flip);
        }
    }


private:
    SDL_Texture* texture;
    int width;
    int height;
};
