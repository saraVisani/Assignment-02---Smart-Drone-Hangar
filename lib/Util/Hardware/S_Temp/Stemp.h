#ifndef __STEMP__
#define __STEMP__

#include "./Hardware/Component.h"

class Stemp : public Component {
    private:
        const float R_FIXED = 10000.0;
        const float R0 = 10000.0;
        const float B = 3950.0;
        const float T0 = 298.15;
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::S_TEMP;
        }
        float readTemperature();
};

#endif