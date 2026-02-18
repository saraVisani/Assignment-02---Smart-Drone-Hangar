#ifndef __TIMER__
#define __TIMER__

class Timer {
    public:
        virtual ~Timer() = default;
        virtual void setupPeriod(int periodMs) = 0;
        virtual void waitForNextTick() = 0;
};

#endif
