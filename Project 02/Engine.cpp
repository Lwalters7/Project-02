#include "Engine.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "SlideComponentX.h"
#include "SlideComponentY.h"
#include "GravityComponent.h"
#include "ControllerComponent.h"
#include "SpawnAndMoveComponent.h"
#include "AsteroidComponent.h"
#include "tinyxml2.h"
#include "Input.h"

using namespace tinyxml2;

// Define static members
bool Engine::isRunning = false;
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
std::vector<std::unique_ptr<GameObject>> Engine::gameObjects;
int Engine::width = 0;
int Engine::height = 0;

double Engine::_deltaTime = 0.0;
Uint32 Engine::_lastFrameTime = 0;

double Engine::deltaTime() {
    return _deltaTime;
}

// Initialize the engine and create a window and renderer
bool Engine::init(const char* title, int width, int height) {
    Engine::width = width;
    Engine::height = height;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    isRunning = true;
    return true;
}

// Event handling (e.g., for quitting the game)
void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        Input::processEvent(event);  // Update input states
    }
}

// Load game objects from an XML file
void Engine::loadLevel(const std::string& fileName) {
    XMLDocument doc;
    if (doc.LoadFile(fileName.c_str()) != XML_SUCCESS) {
        SDL_Log("Failed to load level file: %s", fileName.c_str());
        return;
    }

    XMLElement* level = doc.FirstChildElement("Level");
    if (!level) {
        SDL_Log("No <Level> root element found in %s", fileName.c_str());
        return;
    }

    for (XMLElement* objElem = level->FirstChildElement("GameObject"); objElem; objElem = objElem->NextSiblingElement("GameObject")) {
        auto gameObject = std::make_unique<GameObject>();

        for (XMLElement* compElem = objElem->FirstChildElement(); compElem; compElem = compElem->NextSiblingElement()) {
            std::string componentName = compElem->Name();

            if (componentName == "SpriteComponent") {
                const char* texture = compElem->Attribute("texture");
                if (texture) {
                    gameObject->add<SpriteComponent>(texture);
                }
            }
            else if (componentName == "BodyComponent") {
                int x = compElem->IntAttribute("x");
                int y = compElem->IntAttribute("y");
                gameObject->add<BodyComponent>(x, y);
            }
            else if (componentName == "AsteroidComponent") {
                double spawnInterval = compElem->DoubleAttribute("spawnInterval", 2.0);
                double speed = compElem->DoubleAttribute("speed", 5.0);
                gameObject->add<AsteroidComponent>(spawnInterval, speed);
            }
            else if (componentName == "GravityComponent") {
                gameObject->add<GravityComponent>();
            }
            else if (componentName == "ControllerComponent") {
                gameObject->add<ControllerComponent>();
            }
            else if (componentName == "SlideComponentX") {
                double speed = compElem->DoubleAttribute("speed");
                int leftBound = compElem->IntAttribute("leftBound");
                int rightBound = compElem->IntAttribute("rightBound");
                gameObject->add<SlideComponentX>(speed, leftBound, rightBound);
            }
            else if (componentName == "SlideComponentY") {
                double speed = compElem->DoubleAttribute("speed");
                int topBound = compElem->IntAttribute("topBound");
                int bottomBound = compElem->IntAttribute("bottomBound");
                gameObject->add<SlideComponentY>(speed, topBound, bottomBound);
            }
            else if (componentName == "SpawnAndMoveComponent") {
                double speed = compElem->DoubleAttribute("speed");
                int screenWidth = compElem->IntAttribute("screenWidth");
                int screenHeight = compElem->IntAttribute("screenHeight");
                gameObject->add<SpawnAndMoveComponent>(speed, screenWidth, screenHeight);
            }
        }

        Engine::addGameObject(std::move(gameObject));
    }
}

// Update all game objects
void Engine::update() {
    for (auto& gameObject : gameObjects) {
        gameObject->update();
    }
}

// Render all game objects
void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (auto& gameObject : gameObjects) {
        gameObject->draw();
    }

    SDL_RenderPresent(renderer);
}

// Clean up resources
void Engine::clean() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

// Check if the engine is still running
bool Engine::running() {
    return isRunning;
}

// Add a GameObject to the engine
void Engine::addGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

// Run the main game loop
void Engine::run() {
    _lastFrameTime = SDL_GetTicks();  // Initialize the first frame time

    while (isRunning) {
        Uint32 currentFrameTime = SDL_GetTicks();
        _deltaTime = (currentFrameTime - _lastFrameTime) / 1000.0;  // Convert to seconds
        _lastFrameTime = currentFrameTime;

        handleEvents();
        update();
        render();
        SDL_Delay(16);  // 60 FPS (approximately)

        // Remove destroyed objects
        for (auto it = gameObjects.begin(); it != gameObjects.end();) {
            if ((*it)->isDestroyed()) {
                it = gameObjects.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    clean();
}

// Get the SDL renderer
SDL_Renderer* Engine::getRenderer() {
    return renderer;
}
