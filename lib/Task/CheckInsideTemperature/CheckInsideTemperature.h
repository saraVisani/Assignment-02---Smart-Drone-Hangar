#ifndef __T_CHECK_INSIDE_TEMPERATURE__
#define __T_CHECK_INSIDE_TEMPERATURE__

#include "Task.h"

class CheckInsideTemperature: public Task {
    private:
        unsigned long lastTempCheckTime;
    public:
        inline TaskType getType() override {
            return T_CHECK_INSIDE_TEMPERATURE;
        }
        void tick() override;
};

#endif