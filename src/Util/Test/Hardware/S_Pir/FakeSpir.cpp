#include "FakeSpir.h"

void FakeSpir::init(int pin)
{
    stateOn = false;
}

bool FakeSpir::isDroneDetected() const
{
    return stateOn;
}

void FakeSpir::setDroneDetected(bool detected)
{
    stateOn = detected;
}

void FakeSpir::printDebug() const
{
    bool state = isDroneDetected();
    
    Serial.print("PIR State: ");
    Serial.println(state ? "DRONE DETECTED" : "NO DRONE");
}
