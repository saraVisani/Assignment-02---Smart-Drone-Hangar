#include "Sddd.h"

void Sddd::init(int pin)
{
    pinMode(P_S_DDD_TRIG, OUTPUT);
    pinMode(P_S_DDD_ECHO, INPUT);
    digitalWrite(P_S_DDD_TRIG, LOW);
}

float Sddd::readDistance() {
    digitalWrite(P_S_DDD_TRIG, LOW);    // Assicura che il pin TRIG sia basso
    delayMicroseconds(2);               
    digitalWrite(P_S_DDD_TRIG, HIGH);   // Invia impulso ultrasonico
    delayMicroseconds(10);              // L’impulso dura 10 µs
    digitalWrite(P_S_DDD_TRIG, LOW);    // Ferma impulso

    long duration = pulseIn(P_S_DDD_ECHO, HIGH, 30000); // misura tempo in µs
    lastDistance = duration * 0.034 / 2;               // distanza in cm
    return lastDistance;
}

bool Sddd::readDistanceAvarage(float &avarage, int samples)
{
    float tot = 0;
    int count = 0;
    tot += readDistance();
    if(count == N){
        avarage = tot / samples;
        return true;
    } return false;
}

bool Sddd::isDroneInside()
{
    return readDistanceAvarage() < TAKEOFF_DISTANCE;
}

bool Sddd::isDroneOutside()
{
    return readDistanceAvarage() >= TAKEOFF_DISTANCE;
}

void Sddd::printDistanceDebug()
{
    Serial.print("Distance: ");
    Serial.println(lastDistance);
}
