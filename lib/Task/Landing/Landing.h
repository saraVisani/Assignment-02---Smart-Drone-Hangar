#ifndef __LANDING__
#define __LANDING__

#include "Task.h"

enum class LandingState {
    LANDING,
    WAIT_DRONE_LAND,
};

class Landing: public Task{
    private:
    unsigned long droneLandStartTime;
    LandingState state;
    bool openHangarDoor;
    void landing();
    void monitorDroneLanding();
    void completeLanding();

    public:
    Landing();

    inline TaskType getType() override {
        return TaskType::T_LANDING;
    };
    void tick() override;
};

#endif