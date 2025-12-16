#include "Landing.h"

Landing::Landing()
    : droneLandStartTime(0),
      state(LandingState::WAIT_COMMAND), 
      openHangarDoor(false) 
{}

//va chiamato quando arriva il comando dal dru
void Landing::receiveCommand()
{
    if(state == LandingState::WAIT_COMMAND){
        state = LandingState::LANDING;
    }
}

void Landing::landing()
{
    if(!openHangarDoor){
        servoMotor.open();
        Hardware::updateOpeningDoor();
        lcdDisplay.activateClearFlag();
        lcdDisplay.printLine("LANDING");
        openHangarDoor = true;
        state = LandingState::WAIT_DRONE_LAND;
    }
}

void Landing::monitroDroneLanding()
{
    if(state != LandingState::WAIT_DRONE_LAND || !openHangarDoor) return;
    float distance = sensorDdd.readDistanceAvarage();
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

void Landing::completeLanding()
{
    servoMotor.close();
    Hardware::updateClosingDoor();
    lcdDisplay.activateClearFlag();
    lcdDisplay.printLine("DRONE INSIDE");
    openHangarDoor = false;
    droneLandStartTime = 0;
    state = LandingState::DRONE_INSIDE;
}

void Landing::tick()
{
    servoMotor.update();
    switch (state) {
        case LandingState::WAIT_COMMAND:
            break;
        case LandingState::LANDING:
            landing();
            break;
        case LandingState::WAIT_DRONE_LAND:
            monitroDroneLanding();
            break;
        case LandingState::DRONE_INSIDE:
            break;
    }
}