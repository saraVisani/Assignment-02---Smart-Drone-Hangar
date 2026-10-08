#ifndef __LANDING__
#define __LANDING__

#include "Task/Task.h"

enum class LandingState {
    LANDING,
    WAIT_DRONE_LAND,
};

class Landing: public Task{
    private:
    unsigned long droneLandStartTime = 0;
    LandingState state = LandingState::LANDING;
    bool openHangarDoor;
    void landing();
    void monitorDroneLanding();
    void completeLanding();

    public:
    inline TaskType getType() override {
        return TaskType::T_LANDING;
    };
    void tick() override;
};

#endif