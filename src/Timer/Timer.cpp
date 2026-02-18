#include "RealTimer.h"

void timerISR() {
    // ISR semplice che imposta un flag globale
    extern volatile bool timerFlag;
    timerFlag = true;
}

volatile bool timerFlag = false;

void RealTimer::setupPeriod(int periodMs) {
    period = (unsigned long)periodMs * 1000UL;  // ms → µs
    timerFlag = false;

    Timer1.initialize(period);
    Timer1.attachInterrupt([](){
        timerFlag = true;
    });
}

void RealTimer::waitForNextTick() {
    timerFlag = false;

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    noInterrupts();

    if (!timerFlag) {
        interrupts();
        sleep_cpu();
    } else {
        interrupts();
    }

    sleep_disable();
}
