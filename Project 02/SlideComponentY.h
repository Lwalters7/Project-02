#pragma once
#include "Component.h"
#include "BodyComponent.h"

class SlideComponentY : public Component {
public:
    SlideComponentY(GameObject& parent) : Component(parent) {
        speed =.1;
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

        if (body->y() > bottomY) {
            goingDown = false;
            body->y() = bottomY;
        }
        if (body->y() < topY) {
            goingDown = true;
            body->y() = topY;
        }

        if (goingDown) {
            body->y() += speed;
        }
        else {
            body->y() -= speed;
        }
    }

    void draw() override {
        // SlideComponentY does not need to draw anything.
    }

private:
    double speed;
    bool goingDown{ true };
    int topY;
    int bottomY;
};
