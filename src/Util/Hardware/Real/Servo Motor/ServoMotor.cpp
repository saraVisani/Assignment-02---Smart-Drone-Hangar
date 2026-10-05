#include "ServoMotor.h"

void ServoMotor::init(int pin) {
    motor.attach(P_SERVOMOTOR);
    angle = 0;
    targetAngle = 0;
    closed = true;
    opened = false;
    lastStepTime = 0;
    motor.write(angle);
}

int ServoMotor::angleToPulse(){
    return map(this->angle, 0, 180, 750, 2400);
}

void ServoMotor::setPosition(int angle) {
    this->angle = angle;
    motor.write(angleToPulse());
    opened = (angle == 180);
    closed = (angle == 0);
}

// -------------------------
// GRADUAL MOVEMENT
// -------------------------

void ServoMotor::open() {
    if(targetAngle != 180) targetAngle = 180;
}

void ServoMotor::close() {
    if(targetAngle != 0) targetAngle = 0;
}

void ServoMotor::update() {
    if (angle == targetAngle) return;

    // L'avanzamento avviene ad ogni chiamata dello Scheduler (ogni 10 ms)
    if (angle < targetAngle) {
        angle += stepSize;
        if (angle > targetAngle) angle = targetAngle;
    } else {
        angle -= stepSize;
        if (angle < targetAngle) angle = targetAngle;
    }

    setPosition(angle);
}
