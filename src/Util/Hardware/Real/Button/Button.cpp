#include "Button.h"

unsigned long lastPress = 0;
unsigned long threshold = 20;

void Button::init(int pin) {
    pinMode(B_RESET, INPUT_PULLUP);
    addInterrupt();
}

void Button::addInterrupt() {
    attachInterrupt(digitalPinToInterrupt(B_RESET), irs, FALLING);
    activateInterrupt = true;
}

void Button::irs() {
    if (lastPress == 0 || millis() - lastPress >= threshold) {
        resetAllarm = true;
    }
    lastPress = millis();
}
