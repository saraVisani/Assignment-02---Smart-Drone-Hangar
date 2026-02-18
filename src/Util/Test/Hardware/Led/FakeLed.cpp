#include "FakeLed.h"

void FakeLed::init(int pin) {
    //pinMode(pin, OUTPUT);
    //digitalWrite(pin, LOW);
    this->pin = pin;
    this->stateOn = false;
}

void FakeLed::turnOn() {
    if(!isOn()){
        //digitalWrite(pin, HIGH);
        this->stateOn = true;
    }
}

void FakeLed::turnOff() {
    if(isOn()){
        //digitalWrite(pin, LOW);
        this->stateOn = false;
    }
}
