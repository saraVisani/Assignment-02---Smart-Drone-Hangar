#ifndef __TASK__
#define __TASK__

#include "Globals.h"

class Task
{
    protected:
        int myPeriod;
        int timeElapsed;

    public:
        virtual void init(int period);
        virtual void tick() = 0;
        virtual TaskType getType() = 0;
        bool updateAndCheckTime(int basePeriod);
};

#endif