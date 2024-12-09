#pragma once
#include "Component.h"
#include "Engine.h"
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
        color = { 255, 255, 255, 255 };

    }
    void setAngle(float newAngle) {
        angle = newAngle;
    }
    void setFlip(SDL_RendererFlip newFlip) {
        flip = newFlip;
    }
    void setPosition(float x, float y) {
        position.x = static_cast<int>(x);
        position.y = static_cast<int>(y);
    }
    void update() override {}
    void draw() override {
        float x, y;
        parent().getPosition(x, y);

        SDL_Rect dst = { static_cast<int>(x), static_cast<int>(y), width * SCALE, height * SCALE };
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

        SDL_RenderCopyEx(Engine::getRenderer(), texture, nullptr, &dst, angle, nullptr, flip);

    }
private:
    SDL_Texture* texture; // Texture to render
    int width;            // Width of the sprite
    int height;           // Height of the sprite
    SDL_Color color;      // Current color of the sprite
    static constexpr float SCALE = 3.0f; // Pixels-to-meters conversion factor
    SDL_Point position{ 0, 0 }; // Rendering position
    float angle;
    SDL_RendererFlip flip;           // Flip state (horizontal/vertical/none)

};
