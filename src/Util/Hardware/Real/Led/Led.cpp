#include "Led.h"

void Led::init(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    this->pin = pin;
    this->stateOn = false;
}

void Led::turnOn() {
    if(!isOn()){
        digitalWrite(pin, HIGH);
        this->stateOn = true;
    }
}

void Led::turnOff() {
    if(isOn()){
        digitalWrite(pin, LOW);
        this->stateOn = false;
    }
}
