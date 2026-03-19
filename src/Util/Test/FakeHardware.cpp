#include "FakeHardware.h"
#include "./Util/test/Hardware/Led/FakeLed.h"
#include "./Util/test/Hardware/Button/FakeButton.h"
#include "./Util/test/Hardware/LCD/FakeLcd.h"
#include "./Util/test/Hardware/S_Pir/FakeSpir.h"
#include "./Util/test/Hardware/S_DDD/FakeSddd.h"
#include "./Util/test/Hardware/S_Temp/FakeStemp.h"
#include "./Util/test/Hardware/Servo Motor/FakeServoMotor.h"

Hardware* hw = nullptr;
unsigned long fakeMillis = 0;

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
    Serial.println("Servo motor is opened: " + String(servoMotor->isOpened()));
    Serial.println(State::matchDroneState(IDLE) || State::matchDroneState(OPERATING));
    Serial.println("Current drone state: " + State::currentDroneStateString());
    if(!servoMotor->isOpened() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        Serial.println("Opening door...");
        servoMotor->open();
    }
}

void FakeHardware::closeDoor() {
    if(!servoMotor->isClosed() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        Serial.println("Closing door...");
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