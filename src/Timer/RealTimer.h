#ifndef __REALTIMER__
#define __REALTIMER__

#include "Timer.h"
#include "Util/Libraries/TimerOne/TimerOne.h"
#include <avr/sleep.h>

class RealTimer : public Timer {
private:
    volatile bool flag = false;
    unsigned long period;

public:
    RealTimer() = default;

    void setupPeriod(int periodMs) override;
    void waitForNextTick() override;
};

#endif
