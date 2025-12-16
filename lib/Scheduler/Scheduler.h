#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Task.h"
#include "Globals.h"

#define MAX_TASKS 10

class Scheduler {
    private:
        int basePeriod;
        int nTasks;
        Task *taskList[MAX_TASKS];
        Timer timer;
        bool activateTaskLed;
        /**
         * The isSkipped method checks if a task should be skipped.
         * @param type The type of the task.
         * @return true if the task is to be skipped, false otherwise.
         * Task types that can be skipped:
         * - TakeOff
         * - Landing
         * - LedInAction
         */
        bool isSkipped(TaskType type);
        /**
         * The activateTempTask method checks if temperature-related tasks should be activated.
         * @param type The type of the task.
         */
        bool activateTempTask(TaskType type);
        /**
         * The activateTaskMovement method checks if movement-related tasks should be activated.
         * @param type The type of the task.
         */
        bool activateTaskMovement(TaskType type);
        /**
         * The activateLed method checks if the LED task should be activated.
         * @param type The type of the task.
         */
        bool activateLed(TaskType type);
        /**
         * The activateDoor method checks if the door task should be activated.
         * @param type The type of the task.
         */
        bool activateDoor(TaskType type);

    public:
        void init(int basePeriod);
        virtual bool addTask(Task *task);
        /**
         * The schedule method is called in the main loop to run the scheduler.
         */
        virtual void schedule();
};

#endif