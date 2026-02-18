#ifndef __HARDWARE__
#define __HARDWARE__

#include "Globals.h"
#include "Util/Hardware/Api/IButton.h"
#include "Util/Hardware/Api/ILed.h"
#include "Util/Hardware/Api/ISpir.h"
#include "Util/Hardware/Api/ISddd.h"
#include "Util/Hardware/Api/IStemp.h"
#include "Util/Hardware/Api/ILcd.h"
#include "Util/Hardware/Api/IServoMotor.h"

extern ILed* ledOn;
extern ILed* ledAct;
extern ILed* ledAlarm;
extern IButton* buttonReset;
extern ISpir* sensorPir;
extern ISddd* sensorDdd;
extern IStemp* sensorTemp;
extern ILcd* lcdDisplay;
extern IServoMotor* servoMotor;

class Hardware {
public:
    virtual void initAllHardware() = 0;
    virtual void openDoor() = 0;
    virtual void closeDoor() = 0;
    virtual void setDoorPosition(int angle) = 0;
    virtual void updateClosingDoor() = 0;
    virtual void updateOpeningDoor() = 0;
};

extern Hardware* hw;

#endif
