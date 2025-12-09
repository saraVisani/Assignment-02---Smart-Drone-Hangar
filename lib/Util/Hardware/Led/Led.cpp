#include "Led.h"

void Led::init(int pin = 0) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    this->pin = pin;
    this->stateOn = false;
}

bool Led::isOn() {
    return this->stateOn;
}

void Led::turnOn() {
    digitalWrite(pin, LOW);
    this->stateOn = false;
}

void Led::turnOff() {
    digitalWrite(pin, HIGH);
    this->stateOn = true;
}

void Led::toggle() {
    if (isOn()) {
        turnOff();
    } else {
        turnOn();
    }
}
