#include "LedInAction.h"

void LedInAction::checkChange()
{
    if(State::isNotDroneState(LANDING) && State::isNotDroneState(TAKEOFF)){
       lastBlink = 0;
       ledAct.turnOff();
    }
}

void LedInAction::blinking()
{
    unsigned long now = millis();
    if(lastBlink == 0){
        lastBlink = now;
        ledAct.turnOn();
    }
    if(now-lastBlink >= 500){
        ledAct.toggle();
        lastBlink = 0;
    }
}

void LedInAction::tick()
{
    blinking();
    checkChange();
}