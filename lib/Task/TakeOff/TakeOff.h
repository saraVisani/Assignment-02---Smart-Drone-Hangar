#ifndef __TAKEOFF__
#define __TAKEOFF__

#include "Task.h"

enum class TakeOffState {
    WAIT_COMMAND,
    TAKING_OFF,
    WAIT_DRONE_EXIT,
    DRONE_OUT
};

class TakeOff: public Task{
    private:
    unsigned long droneExitStartTime;
    TakeOffState state;
    bool openHangarDoor;
    void takingOff();
    void monitorDroneExit();
    void completeTakeOff();
    
    public:
    TakeOff();

    void receiveCommand();
    void tick() override;
    inline TaskType getType() override {
        return TaskType::T_TAKEOFF;
    };
};

#endif