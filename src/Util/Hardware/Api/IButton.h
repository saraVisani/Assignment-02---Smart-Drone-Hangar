#ifndef IBUTTON_H
#define IBUTTON_H

#include "./Util/Hardware/Component.h"

class IButton : public Component {
public:
    inline HardwareType getType() override {
        return HardwareType::BUTTON;
    }
    virtual bool isPressed() const = 0;
    virtual void addInterrupt() = 0;
};

#endif