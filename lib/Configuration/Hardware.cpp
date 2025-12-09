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