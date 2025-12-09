#include "Timer.h"

Timer* Timer::instance = nullptr;

Timer::Timer() {
    instance = this;
    flag = false;
}

void Timer::isrCallback() {
    if (instance != nullptr) {
        instance->flag = true;
    }
}

void Timer::setupPeriod(int periodMs) {
    period = (unsigned long)periodMs * 1000UL;  // ms → us

    Timer1.initialize(period);
    Timer1.attachInterrupt(Timer::isrCallback);
}

void Timer::waitForNextTick() {
    flag = false;
    set_sleep_mode(SLEEP_MODE_IDLE);

    sleep_enable();
    noInterrupts();

    if (!flag){
        interrupts();
        sleep_cpu();   // <-- QUI ARDUINO SI ADDORMENTA
    }
    else { // race condition: il timer è già scattato
        interrupts();
    }

    sleep_disable();
}
