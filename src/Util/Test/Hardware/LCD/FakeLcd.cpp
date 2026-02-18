#include "FakeLcd.h"

void FakeLcd::init(int pin) {
    //lcd.init();
    //lcd.backlight();
}

void FakeLcd::printLine(const char *message, int line) {
    cleared = false;
    if(line == 0) {
        //lcd.setCursor(0, 0);
        //lcd.print(message);
        p_1 = true;
    } else if(line == 1) {
        //lcd.setCursor(0, 1);
        //lcd.print(message);
        p_2 = true;
    }
}

void FakeLcd::clear() {
    if(!cleared) {
        //lcd.clear();
        cleared = true;
        p_1 = false;
        p_2 = false;
    }
}

void FakeLcd::clearLine(int line) {
    if(line == 0 && p_1) {
        //lcd.setCursor(0, 0);
        //lcd.print("                ");
        //lcd.setCursor(0, 0);
        p_1 = false;
    } else if(line == 1 && p_2) {
        //lcd.setCursor(0, 1);
        //lcd.print("                ");
        //lcd.setCursor(0, 1);
        p_2 = false;
    }
}