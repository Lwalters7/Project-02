#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <box2d/Box2d.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


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
    static void stop();

    static void checkPlayerEnemyCollision();

    static TTF_Font* font; // Static pointer to the font

    static void addPoints(int value); // Function to add points
    static int getPoints();           // Function to get the current points

    static double deltaTime();
    static b2World& getWorld(); 
    
    static GameObject* player; // Static pointer to the player
    static GameObject* enemy;  // Pointer to the enemy GameObject
    static GameObject* asteroid;


private:
    static bool isRunning;
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static std::vector<std::unique_ptr<GameObject>> gameObjects;

    static double _deltaTime;    
    static Uint32 _lastFrameTime; 
    static b2World world; 

    static int points; // Static variable to track points



};
