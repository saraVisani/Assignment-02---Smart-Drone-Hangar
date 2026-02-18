#include "RealHardware.h"

#include "./Util/Hardware/Component.h"
#include "./Util/Hardware/Real/Led/Led.h"
#include "./Util/Hardware/Real/Button/Button.h"
#include "./Util/Hardware/Real/LCD/Lcd.h"
#include "./Util/Hardware/Real/S_Pir/Spir.h"
#include "./Util/Hardware/Real/S_DDD/Sddd.h"
#include "./Util/Hardware/Real/S_Temp/Stemp.h"
#include "./Util/Hardware/Real/Servo Motor/ServoMotor.h"

Hardware* hw = nullptr;

Led ledOnInstance;
Led ledActInstance;
Led ledAlarmInstance;
Button buttonResetInstance;
Spir sensorPirInstance;
Sddd sensorDddInstance;
Stemp sensorTempInstance;
Lcd lcdDisplayInstance;
ServoMotor servoMotorInstance;

ILed* ledOn = &ledOnInstance;
ILed* ledAct = &ledActInstance;
ILed* ledAlarm = &ledAlarmInstance;
IButton* buttonReset = &buttonResetInstance;
ISpir* sensorPir = &sensorPirInstance;
ISddd* sensorDdd = &sensorDddInstance;
IStemp* sensorTemp = &sensorTempInstance;
ILcd* lcdDisplay = &lcdDisplayInstance;
IServoMotor* servoMotor = &servoMotorInstance;

RealHardware::RealHardware() {
    hw = this;
}

void RealHardware::initAllHardware() {
    ledOn->init(L_ON);
    ledAct->init(L_ACT);
    ledAlarm->init(L_ALARM);
    buttonReset->init();
    sensorPir->init();
    sensorDdd->init();
    sensorTemp->init();
    lcdDisplay->init();
}

void RealHardware::openDoor() {
    if(!servoMotor->isOpened() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        servoMotor->open();
    }
}

void RealHardware::closeDoor() {
    if(!servoMotor->isClosed() && (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING))) {
        servoMotor->close();
    }
}

void RealHardware::setDoorPosition(int angle) {
    if((angle < 0 || angle > 180) || (!servoMotor->greaterThan(angle) && !servoMotor->lessThan(angle))) {
        return;
    }
    if((State::matchDroneState(TAKEOFF) || State::matchDroneState(LANDING)) && servoMotor->lessThan(angle)) {
        return;
    }
    servoMotor->setPosition(angle);
}

void RealHardware::updateClosingDoor() {
    if(servoMotor->isClosing()) servoMotor->update();
}

void RealHardware::updateOpeningDoor() {
    if(servoMotor->isOpening()) servoMotor->update();
}

static RealHardware realHw;
