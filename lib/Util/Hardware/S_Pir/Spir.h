#ifndef __SPIR__
#define __SPIR__

#include "./Hardware/Component.h"

class Spir : public Component {
    private:
    bool stateOn = false;
    
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::S_PIR;
        }
        bool isDroneDetected();
        void printDebug();
};

#endif