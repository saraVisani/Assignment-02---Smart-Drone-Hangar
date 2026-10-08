#include "TakeOff.h"

void TakeOff::takingOff()
{
    if(servoMotor->isClosed()){
        hw->openDoor();
        lcdDisplay->clear();
        lcdDisplay->activateClearFlag();
        lcdDisplay->printLine("TAKE OFF");
        state = TakeOffState::WAIT_DRONE_EXIT;
    }
}

void TakeOff::monitorDroneExit()
{
    if(!servoMotor->isOpened()) return;
    float distance;
    if(sensorDdd->readDistanceAvarage(distance)){
        State::setDistanceFromHangar(distance);
        if(distance >= TAKEOFF_DISTANCE){
            if(droneExitStartTime == 0){
                droneExitStartTime = millis();
            } else if (millis() - droneExitStartTime >= TAKEOFF_TIME){
                completeTakeOff();
            }
        } else {
            droneExitStartTime = 0;
        }
    }
}

void TakeOff::completeTakeOff()
{
    ledOn->turnOff();
    hw->closeDoor();
    lcdDisplay->clear();
    lcdDisplay->printLine("DRONE OUT");
    droneExitStartTime = 0;
    state = TakeOffState::TAKING_OFF;
    State::setDroneState(DroneState::OPERATING);
    lcdDisplay->activateClearFlag();
}

void TakeOff::tick()
{
    switch(state) {
        case TakeOffState::TAKING_OFF:
            takingOff();
            break;
        case TakeOffState::WAIT_DRONE_EXIT:
            monitorDroneExit();
            break;
    }
}