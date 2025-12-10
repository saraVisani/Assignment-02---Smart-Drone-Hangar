#include "ServoMotor.h"

void ServoMotor::init(int pin) {
    motor.attach(P_SERVOMOTOR);
    angle = 0;
    closed = true;
    opened = false;
    motor.write(angle);
}

inline bool ServoMotor::isClosed() {
    return closed;
}

inline bool ServoMotor::isOpened()
{
    return opened;
}

inline bool ServoMotor::greaterThan(int angle)
{
    return angle > this->angle;
}

inline bool ServoMotor::isClosing()
{
    return targetAngle == 0;
}

inline bool ServoMotor::isOpening()
{
    return targetAngle == 180;
}

inline bool ServoMotor::lessThan(int angle)
{
    return angle < this->angle;
}

inline int ServoMotor::getAngle() {
    return angle;
}

void ServoMotor::setPosition(int angle) {
    this->angle = angle;
    motor.write(angle);
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
