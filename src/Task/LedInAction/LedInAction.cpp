#include "LedInAction.h"

void LedInAction::checkChange()
{
    if(State::isNotDroneState(LANDING) && State::isNotDroneState(TAKEOFF)){
        ledAct->turnOff();
    }
}

void LedInAction::blinking()
{
    ledAct->toggle();
}

void LedInAction::tick()
{
    blinking();
    checkChange();
}