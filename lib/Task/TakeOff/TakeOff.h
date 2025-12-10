#ifndef __TAKEOFF__
#define __TAKEOFF__

#include "Task.h"

class TakeOff: public Task{
    public:
    void takingOff();
    void droneHasLeft();
    void tick() override;
    inline TaskType getType() override;
};


#endif