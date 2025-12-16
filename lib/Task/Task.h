#ifndef __TASK__
#define __TASK__

#include "Hardware.h"

class Task
{
    protected:
        int myPeriod;
        int timeElapsed;

    public:
        virtual void init(int period);
        /**
         * The tick method is called by the scheduler when it's time for the task to run.
         */
        virtual void tick() = 0;
        virtual TaskType getType() = 0;
        bool updateAndCheckTime(int basePeriod);
};

#endif