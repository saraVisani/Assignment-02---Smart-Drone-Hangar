#ifndef __REALHARDWARE__
#define __REALHARDWARE__

#include "Hardware.h"

class RealHardware: public Hardware{
public:
    RealHardware();
    void initAllHardware() override;
    void openDoor() override;
    void closeDoor() override;
    void setDoorPosition(int angle) override;
    void updateClosingDoor() override;
    void updateOpeningDoor() override;
};

#endif
