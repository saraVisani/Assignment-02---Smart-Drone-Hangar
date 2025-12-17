#include "Globals.h"

DroneState State::droneState = IDLE;
SystemState State::systemState = OK;

void State::setDroneState(DroneState newState) { droneState = newState; }
void State::setSystemState(SystemState newState) { systemState = newState; }
bool State::matchDroneState(DroneState state) { return droneState == state; }
bool State::matchSystemState(SystemState state) { return systemState == state; }
bool State::isNotDroneState(DroneState state) { return droneState != state; }
bool State::isNotSystemState(SystemState state) { return systemState != state; }

DroneState State::stringToDroneState(const char* stateString) {
    if (strcasecmp(stateString, "idle") == 0) return IDLE;
    if (strcasecmp(stateString, "takeoff") == 0) return TAKEOFF;
    if (strcasecmp(stateString, "operating") == 0) return OPERATING;
    if (strcasecmp(stateString, "landing") == 0) return LANDING;
    return IDLE;
}

SystemState State::stringToSystemState(const char* stateString) {
    if (strcasecmp(stateString, "ok") == 0) return OK;
    if (strcasecmp(stateString, "prealarm") == 0) return PREALARM;
    if (strcasecmp(stateString, "alarm") == 0) return ALARM;
    return OK;
}

String State::droneStateToString(DroneState state) {
    switch (state) {
        case IDLE: return "Idle";
        case TAKEOFF: return "Take off";
        case OPERATING: return "Operating";
        case LANDING: return "Landing";
    }
    return "Unknown";
}

String State::systemStateToString(SystemState state) {
    switch (state) {
        case OK: return "OK";
        case PREALARM: return "Pre-alarm";
        case ALARM: return "Alarm";
    }
    return "Unknown";
}

String State::currentDroneStateString() { return droneStateToString(droneState); }
String State::currentSystemStateString() { return systemStateToString(systemState); }

inline void State::setDistanceToGround(float distance) {
    distanceToGround = distance;
}

inline float State::getDistanceToGround() {
    return distanceToGround;
}

inline void State::addDistanceToGround(float distance) {
    distanceToGround += distance;
}

inline void State::subtractDistanceToGround(float distance) {
    distanceToGround -= distance;
}

inline void State::setTemperatureInside(float temperature) {
    temperatureInside = temperature;
}

inline float State::getTemperatureInside() {
    return temperatureInside;
}

inline void State::setDistanceFromHangar(float distance) {
    distanceFromHangar = distance;
}

inline float State::getDistanceFromHangar() {
    return distanceFromHangar;
}

inline void State::setSingleDistance(float distance) {
    singleDistance = distance;
}

inline float State::getSingleDistance() {
    return singleDistance;
}
