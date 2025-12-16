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
        void tick() override;
        inline TaskType getType() override {
            return T_INPUTOUTPUT;
        }
};

#endif