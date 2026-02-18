#ifndef __LED__
#define __LED__

#include "./Util/Hardware/Api/ILed.h"

class Led: public ILed {
    private:
        bool stateOn = false;
        int pin;
    public:
        void init(int pin = 0) override;
        inline bool isOn() const override{
            return this->stateOn;
        }
        void turnOn() override;
        void turnOff() override;
};

#endif