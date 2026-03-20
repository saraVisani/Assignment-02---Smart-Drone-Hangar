#ifndef __FAKEHARDWARE__
#define __FAKEHARDWARE__

#include "./Configuration/Hardware.h"
#include "./Util/test/Hardware/Led/FakeLed.h"
#include "./Util/test/Hardware/Button/FakeButton.h"
#include "./Util/test/Hardware/LCD/FakeLcd.h"
#include "./Util/test/Hardware/S_Pir/FakeSpir.h"
#include "./Util/test/Hardware/S_DDD/FakeSddd.h"
#include "./Util/test/Hardware/S_Temp/FakeStemp.h"
#include "./Util/test/Hardware/Servo Motor/FakeServoMotor.h"

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
