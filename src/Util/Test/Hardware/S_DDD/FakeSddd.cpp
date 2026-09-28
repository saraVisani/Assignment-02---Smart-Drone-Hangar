#include "FakeSddd.h"

void FakeSddd::init(int pin)
{
    lastDistance = 0;
    count = 0;
    measurementAvailable = true;
}

float FakeSddd::readDistance() 
{
    return lastDistance;
}

bool FakeSddd::readDistanceAvarage(float &avarage, int samples)
{
    if (!measurementAvailable) {
        return false;
    }

    count++;

    if (count == samples) {
        avarage = lastDistance;
        count = 0;
        return true;
    }

    return false;
}

bool FakeSddd::isDroneInside() const
{
    return lastDistance < TAKEOFF_DISTANCE;
}

bool FakeSddd::isDroneOutside() const
{
    return lastDistance >= TAKEOFF_DISTANCE;
}

void FakeSddd::printDistanceDebug() const
{
    Serial.print("DDD Distance: ");
    Serial.println(lastDistance);
}

void FakeSddd::setDistance(float distance)
{
    lastDistance = distance;
}

void FakeSddd::resetSamples()
{
    count = 0;
}

void FakeSddd::setMeasurementAvailable(bool available)
{
    measurementAvailable = available;
}