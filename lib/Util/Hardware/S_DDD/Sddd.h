#ifndef __SDDD__
#define __SDDD__

#include "./Hardware/Component.h"

class Sddd : public Component {
    private:
    float lastDistance = 0;

    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::S_DDD;
        }
        float readDistance();
        float readDistanceAvarage(int samples = 5);
        bool isDroneInside();
        bool isDroneOutside();
        void printDistanceDebug();

};

#endif