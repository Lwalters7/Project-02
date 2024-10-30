#pragma once
#include "Component.h"
#include "BodyComponent.h"

class SlideComponentX : public Component {
public:
    SlideComponentX(GameObject& parent) : Component(parent) {
        speed = .1;
        leftx = 0;
        rightx = Engine::width;
    }

    SlideComponentX(GameObject& parent, double speed) 
        : Component(parent), speed(speed){
        leftx = 0;
        rightx = Engine::width;
    }
    SlideComponentX(GameObject& parent, double speed, int leftx, int rightx) 
        : Component(parent), speed(speed), leftx(leftx), rightx(rightx){}
    
    void update() override {
        auto body = parent().get<BodyComponent>();
        //body->x()+=100*Engine::deltatime;
        if (body->x() > rightx) {
            goingRight = false;
            body->x() = rightx;
        }
        if (body->x() < leftx) {
            goingRight = true;
            body->x() = leftx;
        }


        if (goingRight) {
            body->x() += speed;
        }
        else {
            body->x() -= speed;
        }
    }

    void draw() override {

    }



private:
    double speed;
    bool goingRight{ true };
    int leftx;
    int rightx;
};