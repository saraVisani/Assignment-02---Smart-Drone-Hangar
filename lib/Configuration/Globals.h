#ifndef __GLOBALS__
#define __GLOBALS__

#include "Arduino.h"

/* ---- PINS FOR HARDWARE ---- */
#define     L_ON            2//pin
#define     L_ACT           3//pin
#define     L_ALARM         4//pin
#define     B_RESET         5//pin
#define     P_S_PIR         6//pin
#define     P_S_DDD_ECHO    7//pin
#define     P_S_DDD_TRIG    8//PIN
#define     P_S_TEMP        9//pin
#define     P_SERVOMOTOR    10//pin

/* ---- GLOBAL CONSTANT VARIABLE ---- */
static const int    TAKEOFF_DISTANCE   =      100; //da aggiustare
static const int    LANDING_DISTANCE   =      50; //da aggiustare
static const int    TAKEOFF_TIME       =      5000; //da aggiustare
static const int    LANDING_TIME       =      5000; //da aggiustare
static const int    TEMP_THRESHOLD     =      75; //da aggiustare
static const int    PREALARM_TIME      =      10000; //da aggiustare
static const int    ALARM_TIME         =      20000; //da aggiustare

/* ---- BUTTON INTERUPT ---- */
volatile bool resetAllarm = false; 

/* ---- ENUM FOR THE STATUSES ---- */
typedef enum {
    IDLE,
    TAKEOFF,
    OPERATING,
    LANDING
} DroneState;

typedef enum {
    OK,
    PREALARM,
    ALARM
} SystemState;

/* ---- CLASS STATE ---- */
class State {
public:
    private:
        static DroneState droneState;
        static SystemState systemState;
        static float distanceToGround;
        static float temperatureInside;
        static float distanceFromHangar;
    public:
        static void setDroneState(DroneState newState);
        static void setSystemState(SystemState newState);
        static bool matchDroneState(DroneState state);
        static bool matchSystemState(SystemState state);
        static bool isNotDroneState(DroneState state);
        static bool isNotSystemState(SystemState state);
        static DroneState stringToDroneState(const char* stateString);
        static SystemState stringToSystemState(const char* stateString);
        static String droneStateToString(DroneState state);
        static String systemStateToString(SystemState state);
        static String currentDroneStateString();
        static String currentSystemStateString();
        static inline void setDistanceToGround(float distance);
        static inline float getDistanceToGround();
        static inline void addDistanceToGround(float distance);
        static inline void subtractDistanceToGround(float distance);
        static inline void setTemperatureInside(float temperature) {
            temperatureInside = temperature;
        }
        static inline float getTemperatureInside() {
            return temperatureInside;
        }
        static inline float setDistanceFromHangar(float distance) {
            distanceFromHangar = distance;
        }
        static inline float getDistanceFromHangar() {
            return distanceFromHangar;
        }
};

/* ---- ENUM FOR THE HARDWARE ---- */

typedef enum {
    LED,
    BUTTON,
    LCD,
    S_DDD,
    S_PIR,
    S_TEMP,
    SERVO_MOTOR
} HardwareType;

static inline bool matchHardwareType(HardwareType t1, HardwareType t2) {
    return (t1 == t2);
}

static inline bool isNotHardwareType(HardwareType t1, HardwareType t2) {
    return (t1 != t2);
}

static bool matchHardwareType(HardwareType t1, String t2) {
    HardwareType ht;
    if(t2 == "LED") {
        ht = LED;
    } else if(t2 == "BUTTON") {
        ht = BUTTON;
    } else if(t2 == "LCD") {
        ht = LCD;
    } else if(t2 == "S_DDD") {
        ht = S_DDD;
    } else if(t2 == "S_PIR") {
        ht = S_PIR;
    } else if(t2 == "S_TEMP") {
        ht = S_TEMP;
    } else {
        return false;
    }
    return (t1 == ht);
}

static bool isNotHardwareType(HardwareType t1, String t2) {
    HardwareType ht;
    if(t2 == "LED") {
        ht = LED;
    } else if(t2 == "BUTTON") {
        ht = BUTTON;
    } else if(t2 == "LCD") {
        ht = LCD;
    } else if(t2 == "S_DDD") {
        ht = S_DDD;
    } else if(t2 == "S_PIR") {
        ht = S_PIR;
    } else if(t2 == "S_TEMP") {
        ht = S_TEMP;
    } else {
        return false;
    }
    return (t1 != ht);
}

/* ---- ENUM FOR THE TASKS ---- */

typedef enum {
    T_INPUTOUTPUT,
    T_TAKEOFF,
    T_LANDING,
    T_LEDINACTION,
    T_CHECK_INSIDE_TEMPERATURE,
    T_DOOR
} TaskType;

static inline bool matchTaskType(TaskType t1, TaskType t2) {
    return (t1 == t2);
}

static inline bool isNotTaskType(TaskType t1, TaskType t2) {
    return (t1 != t2);
}

static bool matchTaskType(TaskType t1, String t2) {
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

static bool isNotTaskType(TaskType t1, String t2) {
    TaskType tt;
    if(t2 == "T_INPUTOUTPUT") {
        tt = T_INPUTOUTPUT;
    } else if(t2 == "T_TAKEOFF") {
        tt = T_TAKEOFF;
    } else if(t2 == "T_LANDING") {
        tt = T_LANDING;
    } else if(t2 == "T_LEDINACTION") {
        tt = T_LEDINACTION;
    } else if(t2 == "T_CHECK_INSIDE_TEMPERATURE") {
        tt = T_CHECK_INSIDE_TEMPERATURE;
    } else if(t2 == "T_DOOR") {
        tt = T_DOOR;
    } else {
        return false;
    }
    return (t1 != tt);
}

#endif