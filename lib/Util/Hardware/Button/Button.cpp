#include "Button.h"

void Button::init(int pin = 0){
    pinMode(B_RESET, INPUT_PULLUP);
}

bool Button::isPressed() {
    return digitalRead(B_RESET) == LOW;
}

void Button::addInterrupt(function<void()> fun)
{
    attachInterrupt(digitalPinToInterrupt(B_RESET), fun, FALLING);
    activateInterrupt = true;
}
