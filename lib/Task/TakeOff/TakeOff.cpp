#include "TakeOff.h"

TakeOff::TakeOff()
    : droneExitStartTime(0), 
      state(TakeOffState::TAKING_OFF), 
      openHangarDoor(false) 
{}

void TakeOff::takingOff()
{
    if(!openHangarDoor){
        servoMotor.open();
        Hardware::updateOpeningDoor();
        lcdDisplay.activateClearFlag();
        lcdDisplay.printLine("TAKE OFF");
        openHangarDoor = true;
        state = TakeOffState::WAIT_DRONE_EXIT;
    }
}

void TakeOff::monitorDroneExit()
{
    if(state != TakeOffState::WAIT_DRONE_EXIT || !openHangarDoor) return;
    float distance;
    if(sensorDdd.readDistanceAvarage(distance)){
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
    servoMotor.close();
    Hardware::updateClosingDoor();
    lcdDisplay.activateClearFlag();
    lcdDisplay.printLine("DRONE OUT");
    openHangarDoor = false;
    droneExitStartTime = 0;
    state = TakeOffState::TAKING_OFF;
    State::setDroneState(DroneState::OPERATING);
}

void TakeOff::tick()
{
    servoMotor.update();
    switch(state) {
        case TakeOffState::TAKING_OFF:
            takingOff();
            break;
        case TakeOffState::WAIT_DRONE_EXIT:
            monitorDroneExit();
            break;
    }
}