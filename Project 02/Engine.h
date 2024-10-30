#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <string>

// Forward declaration for GameObject to avoid a full include
class GameObject;

class Engine {
public:
    static int width;
    static int height;

    static bool init(const char* title, int width, int height);
    static void handleEvents();
    static void loadLevel(const std::string& fileName);  // Declaration only
    static void update();
    static void render();
    static void clean();
    static bool running();
    static void addGameObject(std::unique_ptr<GameObject> gameObject);
    static void run();
    static SDL_Renderer* getRenderer();

    static double deltaTime();  // Add this method to get the delta time


private:
    static bool isRunning;
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static std::vector<std::unique_ptr<GameObject>> gameObjects;

    static double _deltaTime;    // Stores the time between frames
    static Uint32 _lastFrameTime; // Stores the time at the last frame
};
