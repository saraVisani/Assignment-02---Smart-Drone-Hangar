#ifndef __HARDWARE__
#define __HARDWARE__

#include "./Hardware/Component.h"
#include "./Hardware/Led/Led.h"
#include "./Hardware/Button/Button.h"
#include "./Hardware/LCD/Lcd.h"
#include "./Hardware/S_Pir/Spir.h"
#include "./Hardware/S_DDD/Sddd.h"
#include "./Hardware/S_Temp/Stemp.h"
#include "./Hardware/Servo Motor/ServoMotor.h"
#include "Globals.h"

extern Led ledOn;
extern Led ledAct;
extern Led ledAlarm;
extern Button buttonReset;
extern Spir sensorPir;
extern Sddd sensorDdd;
extern Stemp sensorTemp;
extern Lcd lcdDisplay;
extern ServoMotor servoMotor;

class Hardware {
private:
    void irs();
    unsigned long lastPress = 0;
    unsigned long threshold = 20;
public:
    static void initAllHardware();
    static void openDoor();
    static void closeDoor();
    static void setDoorPosition(int angle);
    static void updateClosingDoor();
    static void updateOpeningDoor();
};

#endif
