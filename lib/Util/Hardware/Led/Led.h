#ifndef __LED__
#define __LED__

#include "./Hardware/Component.h"

class Led: public Component {
    private:
        bool stateOn = false;
        int pin;
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::LED;
        }
        bool isOn();
        void turnOn();
        void turnOff();
        void toggle();
};

#endif