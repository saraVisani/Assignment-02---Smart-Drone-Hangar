#include "Landing.h"

void Landing::landing()
{
    if(sensorPir->isDroneDetected()){
        if(!servoMotor->isOpened()){
            hw->openDoor();
            lcdDisplay->clear();
            lcdDisplay->printLine("LANDING");
            lcdDisplay->activateClearFlag();
            state = LandingState::WAIT_DRONE_LAND;
        }
    }
}

void Landing::monitorDroneLanding()
{
    if(!servoMotor->isOpened()) return;
    float distance;
    if(sensorDdd->readDistanceAvarage(distance)){
        State::setDistanceToGround(distance);
        if(distance < LANDING_DISTANCE){
            if(droneLandStartTime == 0){
                droneLandStartTime = millis();
            } else if (millis() - droneLandStartTime >= LANDING_TIME){
                completeLanding();
            }
        } else {
            droneLandStartTime = 0;
        }
    }
}

void Landing::completeLanding()
{
    ledOn->turnOn();
    hw->closeDoor();
    lcdDisplay->clear();
    lcdDisplay->activateClearFlag();
    lcdDisplay->printLine("DRONE INSIDE");
    droneLandStartTime = 0;
    state = LandingState::LANDING;
    State::setDroneState(DroneState::IDLE);
}

void Landing::tick()
{
    switch (state) {
        case LandingState::LANDING:
            landing();
            break;
        case LandingState::WAIT_DRONE_LAND:
            monitorDroneLanding();
            break;
    }
}