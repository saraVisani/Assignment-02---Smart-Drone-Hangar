#include "Spir.h"

void Spir::init(int pin)
{
    pinMode(P_S_PIR, INPUT);
}

bool Spir::isDroneDetected()
{
    return digitalRead(P_S_PIR) == HIGH;
}

void Spir::printDebug()
{
    bool state = isDroneDetected();
    Serial.print("PIR State: ");
    Serial.println(state ? "DRONE DETECTED" : "NO DRONE");
}
