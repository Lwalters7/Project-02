#pragma once
#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <SDL2/SDL.h>


class Sounds {
public:
    // Load a sound effect or music file
    static bool load(const std::string& key, const std::string& filePath) {
        Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
        if (!sound) {
            SDL_Log("Failed to load sound: %s", Mix_GetError());
            return false;
        }

        // Store the sound effect in the map
        sounds[key] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(sound);
        return true;
    }

    // Play a sound effect
    static void play(const std::string& key, int loops = 0) {
        auto it = sounds.find(key);
        if (it != sounds.end()) {
            Mix_PlayChannel(-1, it->second.get(), loops);
        }
    }

    // Remove a sound by its key
    static void remove(const std::string& key) {
        sounds.erase(key);
    }

    // Clear all sounds
    static void clear() {
        sounds.clear();
    }

    static void setVolume(const std::string& key, int volume) {
        auto it = sounds.find(key);
        if (it != sounds.end()) {
            Mix_VolumeChunk(it->second.get(), volume);
        }
    }

private:
    // Custom deleter for Mix_Chunk to handle Mix_FreeChunk automatically
    struct SDL_Deleter {
        void operator()(Mix_Chunk* chunk) const {
            if (chunk) {
                Mix_FreeChunk(chunk);
            }
        }
    };


    // Static map to store sounds with custom keys and unique_ptrs for automatic cleanup
    static std::unordered_map<std::string, std::unique_ptr<Mix_Chunk, SDL_Deleter>> sounds;
};
