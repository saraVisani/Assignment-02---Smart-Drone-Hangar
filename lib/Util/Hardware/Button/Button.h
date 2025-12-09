#ifndef __BUTTON__
#define __BUTTON__

#include "./Hardware/Component.h"

class Button : public Component {
public:
    void init(int pin = 0) override;
    inline HardwareType getType() override {
        return HardwareType::BUTTON;
    }
    bool isPressed();
};

#endif
