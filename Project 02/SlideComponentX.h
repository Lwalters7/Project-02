#pragma once
#include "Component.h"
#include "BodyComponent.h"

class SlideComponentX : public Component {
public:
    SlideComponentX(GameObject& parent, double speed = 0.1, int leftBound = 0, int rightBound = Engine::width)
        : Component(parent), speed(speed), leftBound(leftBound), rightBound(rightBound), goingRight(true) {}

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            auto b2Body = body->getBody();
            auto position = b2Body->GetPosition().x * BodyComponent::getScale();
            if (position >= rightBound) {
                goingRight = false;
            }
            else if (position <= leftBound) {
                goingRight = true;
            }
            b2Body->SetLinearVelocity(b2Vec2(goingRight ? speed : -speed, 0.0f)); 
        }
    }
    void draw() override {}
private:
    double speed;   
    bool goingRight; 
    int leftBound;   
    int rightBound;  
};
