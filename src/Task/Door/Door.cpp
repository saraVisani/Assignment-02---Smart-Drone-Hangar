#include "Door.h"

void Door::tick()
{
    servoMotor->update();
    if(servoMotor->isClosing() || servoMotor->isOpening()){
        this->wasMoving = true;
    }
    if(this->wasMoving && (servoMotor->isClosed() || servoMotor->isOpened())){
        this->wasMoving = false;
        ledAct->turnOff();
    }
}