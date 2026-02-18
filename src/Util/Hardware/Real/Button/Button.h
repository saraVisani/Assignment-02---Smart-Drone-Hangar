#ifndef BUTTON_H
#define BUTTON_H

#include "./Util/Hardware/Api/IButton.h"

extern unsigned long lastPress;
extern unsigned long threshold;

class Button : public IButton {
private:
    bool activateInterrupt = false;
    static void irs();

public:
    void init(int pin = 0) override;

    inline bool isPressed() const override {
        return digitalRead(B_RESET) == LOW;
    }

    void addInterrupt() override;
};

#endif