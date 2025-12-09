#include "CheckInsideTemperature.h"

void CheckInsideTemperature::checkTemperature() {
    float currentTemp = sensorTemp.readTemperature();
    unsigned long now = millis();

    //if temp is ok and system not in alarm
    if (currentTemp <= TEMP_THRESHOLD) {
        if (!State::matchSystemState(ALARM)) {
            lastTempCheckTime = 0;
            if (State::matchSystemState(PREALARM)) {
                State::setSystemState(OK);
            }
        }
        return;
    }

    //save first instant when the temp isn't ok
    if (lastTempCheckTime == 0) {
        lastTempCheckTime = now;
    }

    unsigned long elapsed = now - lastTempCheckTime;

    //check if temp wasn't okay for which interval
    if (elapsed >= ALARM_TIME) {
        State::setSystemState(ALARM);
        lcdDisplay.activateClearFlag();
    }
    else if (elapsed >= PREALARM_TIME) {
        State::setSystemState(PREALARM);
    }
}

void CheckInsideTemperature::checkForReset() {
    if(buttonReset.isPressed()){
        State::setSystemState(OK);
        lastTempCheckTime = 0;
        ledAlarm.turnOff();
        lcdDisplay.activateClearFlag();
        lcdDisplay.clear();
    }
}

void CheckInsideTemperature::alarmProtocol(){
    Hardware::closeDoor();
    ledAlarm.turnOn();
    lcdDisplay.clear();
    lcdDisplay.print("ALARM TEMP", "TOO HIGH");
}

void CheckInsideTemperature::tick()
{
    if(State::isNotSystemState(ALARM)){
        checkTemperature();
    } else {
        alarmProtocol();
        checkForReset();
    }
}