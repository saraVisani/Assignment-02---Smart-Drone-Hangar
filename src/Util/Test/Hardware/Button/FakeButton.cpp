#include "FakeButton.h"

unsigned long lastPress = 0;
unsigned long threshold = 20;

void FakeButton::init(int pin) {
    //pinMode(B_RESET, INPUT_PULLUP);
    addInterrupt();
}

void FakeButton::addInterrupt() {
    //attachInterrupt(digitalPinToInterrupt(B_RESET), irs, FALLING);
    activateInterrupt = true;
}
