#ifndef __DOOR_H__
#define __DOOR_H__

#include "Task.h"

class Door : public Task {
    public:
    inline TaskType getType() override {
            return T_DOOR;
        }
    void tick() override;
};

#endif