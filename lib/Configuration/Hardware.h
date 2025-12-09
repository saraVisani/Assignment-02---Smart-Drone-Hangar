#ifndef __HARDWARE__
#define __HARDWARE__

#include "./Hardware/Component.h"
#include "./Hardware/Led/Led.h"
#include "./Hardware/Button/Button.h"
#include "./Hardware/LCD/Lcd.h"
#include "./Hardware/S_Pir/Spir.h"
#include "./Hardware/S_DDD/Sddd.h"
#include "./Hardware/S_Temp/Stemp.h"
#include "Globals.h"

extern Led ledOn;
extern Led ledAct;
extern Led ledAlarm;
extern Button buttonReset;
extern Spir sensorPir;
extern Sddd sensorDdd;
extern Stemp sensorTemp;
extern Lcd lcdDisplay;

class Hardware {
public:
    static void initAllHardware();
};

#endif
