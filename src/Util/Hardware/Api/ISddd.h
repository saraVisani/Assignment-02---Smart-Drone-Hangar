#ifndef __ISDDD__
#define __ISDDD__

#include "./Util/Hardware/Component.h"

class ISddd : public Component {
    public:
        inline HardwareType getType() override {
            return HardwareType::S_DDD;
        }
        virtual float readDistance() = 0;
        virtual bool readDistanceAvarage(float &avarage, int samples = 5) = 0;
        virtual bool isDroneInside() const = 0;
        virtual bool isDroneOutside() const = 0;
        virtual void printDistanceDebug() const = 0;
};

#endif