#include "TakeOff.h"

void TakeOff::takingOff()
{
    servoMotor.open();
    Hardware::updateOpeningDoor()
    lcdDisplay.activateClearFlag();
    lcdDisplay.printLine("TAKE OFF");
}

when the measured distance is greater than D1 for more than T1 seconds,
it is assumed that the drone has exited, and the HD door is closed. The LCD then displays DRONE OUT.

void TakeOff::droneHasLeft()
{
    servoMotor.close();
    Hardware::updateClosingDoor();
    lcdDisplay.activateClearFlag();
    lcdDisplay.printLine("DRONE OUT");
}

void TakeOff::tick()
{
    takingOff();
    droneHasLeft();
}