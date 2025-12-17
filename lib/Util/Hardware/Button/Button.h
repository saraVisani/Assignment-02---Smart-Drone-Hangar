#ifndef __BUTTON__
#define __BUTTON__

#include "./Hardware/Component.h"

class Button : public Component {
private: 
    bool activateInterrupt = false;

public:
    void init(int pin = 0) override;
    inline HardwareType getType() override {
        return HardwareType::BUTTON;
    }
    bool isPressed();
    void addInterrupt(function<void()> fun);
};

#endif
