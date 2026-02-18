#ifndef __FAKEHARDWARE__
#define __FAKEHARDWARE__

#include "./Configuration/Hardware.h"

class FakeHardware : public Hardware {
private:
    //void irs();
    //unsigned long lastPress = 0;
    //unsigned long threshold = 20;
public:
    FakeHardware();
    void initAllHardware() override;
    void openDoor() override;
    void closeDoor() override;
    void setDoorPosition(int angle) override;
    void updateClosingDoor() override;
    void updateOpeningDoor() override;
};

#endif
