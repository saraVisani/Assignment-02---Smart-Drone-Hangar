#include "Lcd.h"

void Lcd::init(int pin) {
    lcd.init();
    lcd.backlight();
}

void Lcd::printLine(const char *message, int line) {
    cleared = false;
    if(line == 0) {
        lcd.setCursor(0, 0);
        lcd.print(message);
        p_1 = true;
    } else if(line == 1) {
        lcd.setCursor(0, 1);
        lcd.print(message);
        p_2 = true;
    }
}

void Lcd::clear() {
    if(!cleared) {
        lcd.clear();
        cleared = true;
        p_1 = false;
        p_2 = false;
    }
}

void Lcd::clearLine(int line) {
    if(line == 0 && p_1) {
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        p_1 = false;
    } else if(line == 1 && p_2) {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        p_2 = false;
    }
}

void Lcd::on() {
    lcd.display();
}

void Lcd::off() {
    lcd.noDisplay();
}
