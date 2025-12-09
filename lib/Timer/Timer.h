#ifndef __TIMER__
#define __TIMER__

#include <./Libraries/TimerOne/TimerOne.h>
#include <avr/sleep.h>

class Timer
{
private:
    volatile bool flag;
    unsigned long period;

    static Timer* instance;
    static void isrCallback();

public:
    Timer();
    void setupPeriod(int periodMs);
    void waitForNextTick();
};

#endif
