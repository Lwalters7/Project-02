#pragma once
#include <SDL2/SDL.h>

class View {
public:
    static View& getInstance() {
        static View instance;
        return instance;
    }

    // Set the position of the view (camera center)
    void setPosition(float x, float y) {
        centerX = x;
        centerY = y;
    }

    // Set the scale (zoom level)
    void setScale(float s) {
        scale = s;
    }

    // Set the rotation of the view (in degrees)
    void setRotation(float angle) {
        rotation = angle;
    }

    // Transform world coordinates to screen coordinates
    SDL_Point worldToScreen(float x, float y) const {
        SDL_Point point;
        point.x = static_cast<int>((x - centerX) * scale + screenWidth / 2);
        point.y = static_cast<int>((y - centerY) * scale + screenHeight / 2);
        return point;
    }

    // Set the screen dimensions
    void setScreenSize(int width, int height) {
        screenWidth = width;
        screenHeight = height;
    }

    // Getters
    float getScale() const { return scale; }
    float getRotation() const { return rotation; }

private:
    View() : centerX(0), centerY(0), scale(1.0f), rotation(0.0f), screenWidth(800), screenHeight(600) {}

    float centerX, centerY;
    float scale;
    float rotation;
    int screenWidth, screenHeight;
};
