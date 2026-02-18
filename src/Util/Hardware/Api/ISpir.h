#ifndef __ISPIR__
#define __ISPIR__

#include "./Util/Hardware/Component.h"

class ISpir : public Component {
    public:
        inline HardwareType getType() override {
            return HardwareType::S_PIR;
        }
        virtual bool isDroneDetected() const = 0;
        virtual void printDebug() const = 0;
};

#endif