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
    if(!isOn){
        digitalWrite(pin, HIGH);
        this->stateOn = true;
    }
}

void Led::turnOff() {
    if(isOn){
        digitalWrite(pin, LOW);
        this->stateOn = false;
    }
}

void Led::toggle() {
    if (isOn()) {
        turnOff();
    } else {
        turnOn();
    }
}
