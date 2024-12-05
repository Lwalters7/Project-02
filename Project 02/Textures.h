#pragma once
#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <unordered_map>
#include <string>
#include <memory>

class Textures {
public:
    // Load a texture from a file and store it with the given key
    static bool load(const std::string& key, const std::string& filePath, SDL_Renderer* renderer) {
        SDL_Surface* tempSurface = IMG_Load(filePath.c_str());  // Using BMP for simplicity
        if (!tempSurface) {
            SDL_Log("Failed to load surface: %s", SDL_GetError());
            return false;
        }

        // Convert the surface into a texture
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        if (!texture) {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            return false;
        }

        // Store the texture in the map using a unique pointer
        textures[key] = std::unique_ptr<SDL_Texture, SDL_Deleter>(texture);
        return true;
    }

    // Get a texture by its key
    static SDL_Texture* get(const std::string& key) {
        auto it = textures.find(key);
        if (it != textures.end()) {
            return it->second.get();  // Return raw pointer to the texture
        }
        return nullptr;
    }

    // Remove a texture by its key
    static void remove(const std::string& key) {
        textures.erase(key);
    }

    // Clear all textures
    static void clear() {
        textures.clear();
    }

private:
    // Custom deleter for SDL_Texture to handle SDL_DestroyTexture automatically
    struct SDL_Deleter {
        void operator()(SDL_Texture* texture) const {
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
    };

    // Static map to store textures with custom keys and unique_ptrs for automatic cleanup
    static std::unordered_map<std::string, std::unique_ptr<SDL_Texture, SDL_Deleter>> textures;
};
