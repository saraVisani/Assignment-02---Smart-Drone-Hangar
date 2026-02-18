#include "Globals.h"

volatile bool resetAllarm = false;


bool matchHardwareType(HardwareType t1, String t2) {
    HardwareType ht;
    if(t2 == "LED") ht = LED;
    else if(t2 == "BUTTON") ht = BUTTON;
    else if(t2 == "LCD") ht = LCD;
    else if(t2 == "S_DDD") ht = S_DDD;
    else if(t2 == "S_PIR") ht = S_PIR;
    else if(t2 == "S_TEMP") ht = S_TEMP;
    else return false;

    return t1 == ht;
}

bool isNotHardwareType(HardwareType t1, String t2) {
    return !matchHardwareType(t1, t2);
}

bool matchTaskType(TaskType t1, String t2) {
    TaskType tt;
    if(t2 == "T_INPUTOUTPUT") {
        tt = T_INPUTOUTPUT;
    } else if(t2 == "T_TAKEOFF") {
        tt = T_TAKEOFF;
    } else if(t2 == "T_LANDING") {
        tt = T_LANDING;
    } else if(t2 == "T_CHECK_INSIDE_TEMPERATURE") {
        tt = T_CHECK_INSIDE_TEMPERATURE;
    } else if(t2 == "T_LEDINACTION") {
        tt = T_LEDINACTION;
    } else if(t2 == "T_DOOR") {
        tt = T_DOOR;
    } else {
        return false;
    }
    return (t1 == tt);
}

bool isNotTaskType(TaskType t1, String t2) {
    return !(matchTaskType(t1, t2));
}

DroneState State::droneState = IDLE;
SystemState State::systemState = OK;
float State::distanceToGround = 0.0f;
float State::temperatureInside = 0.0f;
float State::distanceFromHangar = 0.0f;
float State::singleDistance = 0.0f;

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
