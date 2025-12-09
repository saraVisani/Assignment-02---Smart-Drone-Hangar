#include "ServoMotor.h"

void ServoMotor::init(int pin) {
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

inline bool ServoMotor::lessThan(int angle)
{
    return angle < this->angle;
}

inline int ServoMotor::getAngle() {
    return angle;
}

void ServoMotor::close()
{
}

void ServoMotor::open()
{
}

void ServoMotor::setPosition(int angle) {
    this->angle = angle;
}
