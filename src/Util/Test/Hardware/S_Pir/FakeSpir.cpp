#include "FakeSpir.h"

void FakeSpir::init(int pin)
{
    //pinMode(P_S_PIR, INPUT);
}

bool FakeSpir::isDroneDetected() const
{
    //return digitalRead(P_S_PIR) == HIGH;
    return false;
}

void FakeSpir::printDebug() const
{
    bool state = isDroneDetected();
    Serial.print("PIR State: ");
    Serial.println(state ? "DRONE DETECTED" : "NO DRONE");
}
