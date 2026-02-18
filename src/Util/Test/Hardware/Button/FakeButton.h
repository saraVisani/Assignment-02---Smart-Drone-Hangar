#ifndef FAKEBUTTON_H
#define FAKEBUTTON_H

#include "./Util/Hardware/Api/IButton.h"

class FakeButton : public IButton {
private:
    bool activateInterrupt = false;

public:
    void init(int pin = 0) override;

    inline bool isPressed() const override {
        //return digitalRead(B_RESET) == LOW;
        return false;
    }

    void addInterrupt() override ;
};

#endif