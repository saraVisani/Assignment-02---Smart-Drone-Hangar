#include "Landing.h"

Landing::Landing()
    : droneLandStartTime(0),
      state (LandingState::LANDING),
      openHangarDoor(false) 
{}

void Landing::landing()
{
    if(sensorPir.isDroneDetected()){
        if(!openHangarDoor){
            servoMotor.open();
            Hardware::updateOpeningDoor();
            lcdDisplay.activateClearFlag();
            lcdDisplay.printLine("LANDING");
            openHangarDoor = true;
            state = LandingState::WAIT_DRONE_LAND;
        }
    }
}

void Landing::monitorDroneLanding()
{
    if(state != LandingState::WAIT_DRONE_LAND || !openHangarDoor) return;
    float distance;
    if(sensorDdd.readDistanceAvarage(distance)){
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
    servoMotor.close();
    Hardware::updateClosingDoor();
    lcdDisplay.activateClearFlag();
    lcdDisplay.printLine("DRONE INSIDE");
    openHangarDoor = false;
    droneLandStartTime = 0;
    state = LandingState::LANDING;
    State::setDroneState(DroneState::IDLE);
}

void Landing::tick()
{
    servoMotor.update();
    switch (state) {
        case LandingState::LANDING:
            landing();
            break;
        case LandingState::WAIT_DRONE_LAND:
            monitorDroneLanding();
            break;
    }
}