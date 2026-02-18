#ifndef __FAKETASK__
#define __FAKETASK__

#include "./Task/Task.h"

class FakeTask : public Task
{
    protected:
        int count = 0;
        TaskType type;

    public:
        FakeTask(TaskType t);
        void init(int period);
        void tick();
        TaskType getType();
        int inline getCount(){
            return count;
        }
        void reset();
};

#endif