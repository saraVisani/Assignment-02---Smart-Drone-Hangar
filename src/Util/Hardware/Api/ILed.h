#ifndef __ILED__
#define __ILED__

#include "./Util/Hardware/Component.h"

class ILed : public Component {
public:
    inline HardwareType getType() override {
        return HardwareType::LED;
    }
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual bool isOn() const = 0;

    void toggle() {
        if (isOn()) turnOff();
        else turnOn();
    }
};

#endif