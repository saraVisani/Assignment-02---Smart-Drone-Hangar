#ifndef __STEMP__
#define __STEMP__

#include "./Hardware/Component.h"

class Stemp : public Component {
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::S_TEMP;
        }
};

#endif