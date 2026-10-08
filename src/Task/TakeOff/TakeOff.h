#ifndef __TAKEOFF__
#define __TAKEOFF__

#include "Task/Task.h"

enum class TakeOffState {
    TAKING_OFF,
    WAIT_DRONE_EXIT,
};

class TakeOff: public Task{
    private:
    unsigned long droneExitStartTime = 0;
    TakeOffState state = TakeOffState::TAKING_OFF;
    void takingOff();
    void monitorDroneExit();
    void completeTakeOff();

    public:
    void receiveCommand();
    void tick() override;
    inline TaskType getType() override {
        return TaskType::T_TAKEOFF;
    };
};

#endif