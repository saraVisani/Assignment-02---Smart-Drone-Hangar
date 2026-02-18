#include "FakeServoMotor.h"

void FakeServoMotor::init(int pin) {
    angle = 0;
    closed = true;
    opened = false;
    //motor.write(angle);
}

void FakeServoMotor::setPosition(int angle) {
    this->angle = angle;
    //motor.write(angle);
    opened = (angle == 180);
    closed = (angle == 0);
}

// -------------------------
// GRADUAL MOVEMENT
// -------------------------

void FakeServoMotor::open() {
    if(targetAngle != 180) targetAngle = 180;
}

void FakeServoMotor::close() {
    if(targetAngle != 0) targetAngle = 0;
}

void FakeServoMotor::update() {
    if (angle == targetAngle) return;

    unsigned long now = millis();
    if (now - lastStepTime < stepDelay) return;
    lastStepTime = now;

    if (angle < targetAngle) {
        angle += stepSize;
        if (angle > targetAngle) angle = targetAngle;
    }
    else {
        angle -= stepSize;
        if (angle < targetAngle) angle = targetAngle;
    }

    setPosition(angle);
}
