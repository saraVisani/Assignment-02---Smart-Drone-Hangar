#ifndef __DOOR_H__
#define __DOOR_H__

#include "Task/Task.h"

class Door : public Task {
    private:
        bool wasMoving = false;
    public:
    inline TaskType getType() override {
            return T_DOOR;
        }
    void tick() override;
};

#endif