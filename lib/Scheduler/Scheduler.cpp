#include "Scheduler.h"

bool Scheduler::isSkipped(TaskType type) {
    return  ((matchTaskType(type, T_TAKEOFF) || matchTaskType(type, T_LANDING) || matchTaskType(type, T_LEDINACTION)) &&
            (State::matchDroneState(IDLE) || State::matchDroneState(OPERATING)) &&
            State::isNotSystemState(OK));
}

bool Scheduler::activateTempTask(TaskType type) {
    bool isTempTask = matchTaskType(type, T_CHECK_INSIDE_TEMPERATURE);
    return !isTempTask || State::isNotDroneState(OPERATING);
}

bool Scheduler::activateTaskMovement(TaskType type)
{
    if(isNotTaskType(type, T_TAKEOFF) && isNotTaskType(type, T_LANDING)){
        return true;
    }

    // Drone in TAKEOFF → attiva solo la task T_TAKEOFF
    if (State::matchDroneState(TAKEOFF) && matchTaskType(type, T_TAKEOFF)) {
        activateTaskLed = true;
        return true;
    }

    // Drone in LANDING → attiva solo la task T_LANDING
    if (State::matchDroneState(LANDING) && matchTaskType(type, T_LANDING)) {
        activateTaskLed = true;
        return true;
    }

    return false;
}

bool Scheduler::activateLed(TaskType type)
{
    if(isNotTaskType(type, T_LEDINACTION)){
        return true;
    }

    if(activateLed){
        activateTaskLed = false;
        return true;
    }

    return false;
}

bool Scheduler::activateDoor(TaskType type)
{
    if(isNotTaskType(type, T_DOOR)){
        return true;
    }
    return (servoMotor.isOpening() && !servoMotor.isOpened() )
            || (!servoMotor.isClosed() && servoMotor.isClosing());
}

void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    timer.setupPeriod(basePeriod);
    nTasks = 0;
    activateTaskLed = false;
}

bool Scheduler::addTask(Task *task) {
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

void Scheduler::schedule() {
    timer.waitForNextTick();
    for (int i = 0; i < nTasks; i++)
    {
        if (    !isSkipped(taskList[i]->getType())
                && taskList[i]->updateAndCheckTime(basePeriod)
                && activateTempTask(taskList[i]->getType())
                && activateTaskMovement(taskList[i]->getType())
                && activateLed(taskList[i]->getType())
                && activateDoor(taskList[i]->getType())    ){
            taskList[i]->tick();
        }
    }
}