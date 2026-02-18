#include "FakeHardware.h"
#include "./Util/test/Hardware/Led/FakeLed.h"
#include "./Util/test/Hardware/Button/FakeButton.h"
#include "./Util/test/Hardware/LCD/FakeLcd.h"
#include "./Util/test/Hardware/S_Pir/FakeSpir.h"
#include "./Util/test/Hardware/S_DDD/FakeSddd.h"
#include "./Util/test/Hardware/S_Temp/FakeStemp.h"
#include "./Util/test/Hardware/Servo Motor/FakeServoMotor.h"

Hardware* hw = nullptr;

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

void FakeHardware::initAllHardware() {}

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