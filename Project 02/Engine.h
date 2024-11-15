#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <string>

class GameObject;

class Engine {
public:
    static int width;
    static int height;

    static bool init(const char* title, int width, int height);
    static void handleEvents();
    static void loadLevel(const std::string& fileName);
    static void update();
    static void render();
    static void clean();
    static bool running();
    static void addGameObject(std::unique_ptr<GameObject> gameObject);
    static void run();
    static SDL_Renderer* getRenderer();

    static double deltaTime();

private:
    static bool isRunning;
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static std::vector<std::unique_ptr<GameObject>> gameObjects;

    static double _deltaTime;       // Time between frames in seconds
    static Uint32 _lastFrameTime;   // Time at the last frame
};
