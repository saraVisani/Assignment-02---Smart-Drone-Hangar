#ifndef __LANDING__
#define __LANDING__

#include "Task.h"

class Landing: public Task{
    public:
    void tick() override;
    inline TaskType getType() override;
};

#endif