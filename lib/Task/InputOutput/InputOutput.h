#ifndef __INPUTOUTPUT__
#define __INPUTOUTPUT__

#include "Task.h"

class InputOutput: public Task {

    private:
        inline bool isHangarAvailable();
        void read();
        void send();
        void logs();

    public:
    void init(int period) override {
            Task::init(period);
            Serial.setTimeout(10);
        }
        void tick() override;
        inline TaskType getType() override {
            return T_INPUTOUTPUT;
        }
};

#endif