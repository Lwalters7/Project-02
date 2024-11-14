#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "Engine.h"

class SlideComponentX : public Component {
public:
    SlideComponentX(GameObject& parent) : Component(parent) {
        speed = 10.0;
        leftx = 0;
        rightx = Engine::width;
    }

    SlideComponentX(GameObject& parent, double speed)
        : Component(parent), speed(speed) {
        leftx = 0;
        rightx = Engine::width;
    }

    SlideComponentX(GameObject& parent, double speed, int leftx, int rightx)
        : Component(parent), speed(speed), leftx(leftx), rightx(rightx) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (!body) return;

        if (body->x() > rightx) {
            goingRight = false;
            body->x() = rightx;
        }
        if (body->x() < leftx) {
            goingRight = true;
            body->x() = leftx;
        }

        double movement = speed * Engine::deltaTime();
        if (goingRight) {
            body->x() += movement;
        }
        else {
            body->x() -= movement;
        }
    }

    void draw() override {}

private:
    double speed;
    bool goingRight{ true };
    int leftx;
    int rightx;
};
