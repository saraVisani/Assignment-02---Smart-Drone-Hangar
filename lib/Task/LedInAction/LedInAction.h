#ifndef __LEDINACTION__
#define __LEDINACTION__

#include "Task.h"

class LedInAction: public Task{
    public:
    void tick() override;
    inline TaskType getType() override;
}
