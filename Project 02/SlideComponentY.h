#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "Engine.h"

class SlideComponentY : public Component {
public:
    SlideComponentY(GameObject& parent) : Component(parent) {
        speed = 100.0; 
        topY = 0;
        bottomY = Engine::height;
    }

    SlideComponentY(GameObject& parent, double speed)
        : Component(parent), speed(speed) {
        topY = 0;
        bottomY = Engine::height;
    }

    SlideComponentY(GameObject& parent, double speed, int topY, int bottomY)
        : Component(parent), speed(speed), topY(topY), bottomY(bottomY) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (!body) return;

        if (body->y() > bottomY) {
            goingDown = false;
            body->y() = bottomY;
        }
        if (body->y() < topY) {
            goingDown = true;
            body->y() = topY;
        }

        double movement = speed * Engine::deltaTime();
        if (goingDown) {
            body->y() += movement;
        }
        else {
            body->y() -= movement;
        }
    }

    void draw() override {
    }

private:
    double speed;
    bool goingDown{ true };
    int topY;
    int bottomY;
};
