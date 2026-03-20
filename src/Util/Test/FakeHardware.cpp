#include "FakeHardware.h"

Hardware* hw = nullptr;
unsigned long fakeMillis = 0;
SerialMock Serial;

FakeLed ledOnInstance;
FakeLed ledActInstance;
FakeLed ledAlarmInstance;
FakeButton buttonResetInstance;
FakeSpir sensorPirInstance;
FakeSddd sensorDddInstance;
FakeStemp sensorTempInstance;
FakeLcd lcdDisplayInstance;
FakeServoMotor servoMotorInstance;

ILed* ledOn = &ledOnInstance;
ILed* ledAct = &ledActInstance;
ILed* ledAlarm = &ledAlarmInstance;
IButton* buttonReset = &buttonResetInstance;
ISpir* sensorPir = &sensorPirInstance;
ISddd* sensorDdd = &sensorDddInstance;
IStemp* sensorTemp = &sensorTempInstance;
ILcd* lcdDisplay = &lcdDisplayInstance;
IServoMotor* servoMotor = &servoMotorInstance;

FakeHardware::FakeHardware() {
    hw = this;
}

void FakeHardware::initAllHardware() {
    ledOn->init(L_ON);
    ledAct->init(L_ACT);
    ledAlarm->init(L_ALARM);
    buttonReset->init();
    sensorPir->init();
    sensorDdd->init();
    sensorTemp->init();
    lcdDisplay->init();
    servoMotor->init();
}

void FakeHardware::openDoor() {
    if(!servoMotor->isOpened() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        servoMotor->open();
    }
}

void FakeHardware::closeDoor() {
    if(!servoMotor->isClosed() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        servoMotor->close();
    }
}

void FakeHardware::setDoorPosition(int angle) {
    if((angle < 0 || angle > 180) || (!servoMotor->greaterThan(angle) && !servoMotor->lessThan(angle))) {
        return;
    }
    if((State::matchDroneState(TAKEOFF) || State::matchDroneState(LANDING)) && servoMotor->lessThan(angle)) {
        return;
    }
    servoMotor->setPosition(angle);
}

void FakeHardware::updateClosingDoor() {
    if(servoMotor->isClosing()) servoMotor->update();
}

void FakeHardware::updateOpeningDoor() {
    if(servoMotor->isOpening()) servoMotor->update();
}

static FakeHardware fakeHw;