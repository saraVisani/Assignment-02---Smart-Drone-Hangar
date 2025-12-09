#include "Hardware.h"

Led ledOn;
Led ledAct;
Led ledAlarm;
Button buttonReset;
Spir sensorPir;
Sddd sensorDdd;
Stemp sensorTemp;
Lcd lcdDisplay;

void Hardware::initAllHardware() {
    Serial.begin(9600);
    ledOn.init(L_ON);
    ledAct.init(L_ACT);
    ledAlarm.init(L_ALARM);
    buttonReset.init();
    sensorPir.init();
    sensorDdd.init();
    sensorTemp.init();
    lcdDisplay.init();
}

void Hardware::openDoor() {
    if(!servoMotor.isOpened() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        servoMotor.open();
    }
}

void Hardware::closeDoor() {
    if(!servoMotor.isClosed() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        servoMotor.close();
    }
}

void Hardware::setDoorPosition(int angle) {
    if((angle < 0 || angle > 180) || (!servoMotor.greaterThan(angle) && !servoMotor.lessThan(angle))) {
        return;
    }
    if((State::matchDroneState(TAKEOFF) || State::matchDroneState(LANDING)) && servoMotor.lessThan(angle)) {
        return;
    }
    servoMotor.setPosition(angle);
}
