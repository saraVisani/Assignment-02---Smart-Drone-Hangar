#include "Scheduler.h"

bool Scheduler::isSkipped(TaskType type)
{
    return  ((matchTaskType(type, T_TAKEOFF) || matchTaskType(type, T_LANDING)) &&
            (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING)) &&
            State::isNotSystemState(OK));
}

void Scheduler::init(int basePeriod)
{
    this->basePeriod = basePeriod;
    timer.setupPeriod(basePeriod);
    nTasks = 0;
}

bool Scheduler::addTask(Task *task)
{
    if (nTasks < MAX_TASKS - 1)
    {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    }
    else
    {
        return false;
    }
}

void Scheduler::schedule()
{
    timer.waitForNextTick();
    for (int i = 0; i < nTasks; i++)
    {
        if (!isSkipped(taskList[i]->getType()) && taskList[i]->updateAndCheckTime(basePeriod))
        {
            taskList[i]->tick();
        }
    }
}