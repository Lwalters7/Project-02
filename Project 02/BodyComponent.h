#pragma once
#include "Component.h"

class BodyComponent : public Component {
public:
    BodyComponent(GameObject& owner, double x, double y)
        : Component(owner), _x(x), _y(y), facingLeft(false), _velocityY(0.0), _angle(0.0) {}

    // Position accessors
    double& x() { return _x; }
    double& y() { return _y; }

    // Velocity accessors
    double& velocityY() { return _velocityY; }

    void setVelocityY(double vY) { _velocityY = vY; }

    bool isFacingLeft() const { return facingLeft; }
    void setFacingLeft(bool left) { facingLeft = left; }

    // Angle accessor
    double angle() const { return _angle; }

    void updateAngle() {
        double calculatedAngle = 0.0;

        // Calculate the angle based on vertical velocity with different multipliers
        if (_velocityY < 0.0) {
            // Moving up: apply a larger multiplier for faster tilt
            calculatedAngle = atan2(_velocityY, 1.0) * (180.0 / M_PI) * 0.5;  // Adjust upward multiplier
        }
        else if (_velocityY > 0.0) {
            // Moving down: apply a smaller multiplier for slower tilt
            calculatedAngle = atan2(_velocityY, 1.0) * (180.0 / M_PI) * 0.2;  // Adjust downward multiplier
        }

        // Invert the angle if facing left
        if (facingLeft) {
            _angle = -calculatedAngle;
        }
        else {
            _angle = calculatedAngle;
        }
    }

    // Update position based on current velocity and angle
    void update() override {
        _y += _velocityY;
        updateAngle();  // Update angle based on horizontal direction only
    }

    void draw() override {}

private:
    double _x, _y;            // Position coordinates
    double _velocityY;  // Velocity in x and y directions
    double _angle;            // Angle to face left or right
    bool facingLeft;
};
