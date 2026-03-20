#ifndef __FAKELED__
#define __FAKELED__

#include "./Util/Hardware/Api/ILed.h"

class FakeLed: public ILed {
    private:
        bool stateOn = false;
        int onCount = 0;
        int offCount = 0;
        int pin;
    public:
        void init(int pin = 0) override;
        void turnOn() override;
        void turnOff() override;
        inline int getOnCount() const{
            return onCount;
        }
        inline int getOffCount() const{
            return offCount;
        }
        void reset();
        inline bool isOn() const override {
            return this->stateOn;
        }
};

#endif