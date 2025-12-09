#include "Task.h"

void Task::init(int period)
{
    myPeriod = period;
    timeElapsed = 0;
}

bool Task::updateAndCheckTime(int basePeriod)
{
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod)
    {
        timeElapsed = 0;
        return true;
    }
    return false;
}
