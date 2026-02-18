#ifndef __ISTEMP__
#define __ISTEMP__

#include "./Util/Hardware/Component.h"

class IStemp : public Component {
    public:
        inline HardwareType getType() override {
            return HardwareType::S_TEMP;
        }
        virtual float readTemperature() const = 0;
};

#endif