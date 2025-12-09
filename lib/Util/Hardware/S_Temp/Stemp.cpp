#include "Stemp.h"

void Stemp::init(int pin) {
    pinMode(P_S_TEMP, INPUT);
}

float Stemp::readTemperature() {
    int raw = analogRead(P_S_TEMP);
    float Vout = raw * (5.0 / 1023.0);

    float R = R_FIXED * (5.0 / Vout - 1);

    float temperatureK = 1.0 / (1.0 / T0 + (1.0 / B) * log(R / R0));
    return temperatureK - 273.15;
}
