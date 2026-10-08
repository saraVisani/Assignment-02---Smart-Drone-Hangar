#ifndef __T_CHECK_INSIDE_TEMPERATURE__
#define __T_CHECK_INSIDE_TEMPERATURE__

#include "Task/Task.h"

class CheckInsideTemperature: public Task {
    private:
        unsigned long lastTempCheckTime = 0;
        unsigned long changeLine;
        bool switchLine = false;
        bool rewrite = false;
        void checkTemperature();
        void alarmProtocol();
        void checkForReset();
    public:
        inline TaskType getType() override {
            return T_CHECK_INSIDE_TEMPERATURE;
        }
        void tick() override;
};

#endif