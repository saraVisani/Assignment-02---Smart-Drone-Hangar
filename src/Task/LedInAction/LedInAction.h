#ifndef __LEDINACTION__
#define __LEDINACTION__

#include "Task/Task.h"

class LedInAction: public Task{
    public:
        void checkChange();
        void blinking();
        void tick() override;
        inline TaskType getType() override{
            return TaskType::T_LEDINACTION;
        }
};
#endif