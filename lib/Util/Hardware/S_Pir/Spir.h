#ifndef __SPIR__
#define __SPIR__

#include "./Hardware/Component.h"

class Spir : public Component {
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::S_PIR;
        }
};

#endif