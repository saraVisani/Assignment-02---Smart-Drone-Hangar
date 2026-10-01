#include "Stemp.h"

void Stemp::init(int pin) {
    pinMode(P_S_TEMP, INPUT);
}

float Stemp::readTemperature() const {
    int raw = analogRead(P_S_TEMP);
    if(raw != 0){
        float R = R_FIXED * ((1023.0 - (float)raw) / (float)raw);
        float temperatureK = 1.0 / ((1.0 / T0) + (1.0 / B) * log(R / R0));
        return temperatureK - 273.15;
    }
    return 0;
}
