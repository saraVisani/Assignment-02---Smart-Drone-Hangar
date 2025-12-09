#ifndef __T_CHECK_INSIDE_TEMPERATURE__
#define __T_CHECK_INSIDE_TEMPERATURE__

#include "Task.h"

class CheckInsideTemperature: public Task {
    private:
        unsigned long lastTempCheckTime;
        void checkTemperature();
        void alarmProtocol();
    public:
        inline TaskType getType() override {
            return T_CHECK_INSIDE_TEMPERATURE;
        }
        void tick() override;
        void init(int period) override {
            Task::init(period);
            lastTempCheckTime = millis();
        }
};

#endif