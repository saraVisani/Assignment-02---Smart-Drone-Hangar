#ifndef __SDDD__
#define __SDDD__

#include "./Hardware/Component.h"

class Sddd : public Component {
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::S_DDD;
        }
};

#endif