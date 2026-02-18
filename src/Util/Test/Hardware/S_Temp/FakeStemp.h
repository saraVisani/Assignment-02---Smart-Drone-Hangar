#ifndef __FAKESTEMP__
#define __FAKESTEMP__

#include "./Util/Hardware/Api/IStemp.h"

class FakeStemp : public IStemp {
    private:
        const float R_FIXED = 10000.0;
        const float R0 = 10000.0;
        const float B = 3950.0;
        const float T0 = 298.15;
    public:
        void init(int pin = 0) override;
        float readTemperature() const override;
};

#endif