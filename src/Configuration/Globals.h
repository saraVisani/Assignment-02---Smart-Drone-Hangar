#ifndef GLOBALS
#define GLOBALS

#include "ArduinoCompability.h"

/* ---- PINS FOR HARDWARE ---- */
#define L_ON 2          // pin
#define L_ACT 3         // pin
#define L_ALARM 8       // pin
#define B_RESET 5       // pin
#define P_S_PIR 6       // pin
#define P_S_DDD_ECHO 7  // pin
#define P_S_DDD_TRIG 8  // PIN
#define P_S_TEMP 9      // pin
#define P_SERVOMOTOR 10 // pin

/* ---- GLOBAL CONSTANT VARIABLE ---- */
static const int TAKEOFF_DISTANCE = 100; // da aggiustare
static const int LANDING_DISTANCE = 50;  // da aggiustare
static const int TAKEOFF_TIME = 5000;    // da aggiustare
static const int LANDING_TIME = 5000;    // da aggiustare
static const int TEMP_THRESHOLD = 75;    // da aggiustare
static const int PREALARM_TIME = 10000;  // da aggiustare
static const int ALARM_TIME = 20000;     // da aggiustare

/* ---- BUTTON INTERUPT ---- */
extern volatile bool resetAllarm;

/* ---- ENUM FOR THE STATUSES ---- */
typedef enum
{
    IDLE,
    TAKEOFF,
    OPERATING,
    LANDING
} DroneState;

typedef enum
{
    OK,
    PREALARM,
    ALARM
} SystemState;

/* ---- CLASS STATE ---- */
class State
{
public:
private:
    static DroneState droneState;
    static SystemState systemState;
    static float distanceToGround;
    static float temperatureInside;
    static float distanceFromHangar;
    static float singleDistance;

public:
    static void setDroneState(DroneState newState);
    static void setSystemState(SystemState newState);
    static bool matchDroneState(DroneState state);
    static bool matchSystemState(SystemState state);
    static bool isNotDroneState(DroneState state);
    static bool isNotSystemState(SystemState state);
    static DroneState stringToDroneState(const char *stateString);
    static SystemState stringToSystemState(const char *stateString);
    static String droneStateToString(DroneState state);
    static String systemStateToString(SystemState state);
    static String currentDroneStateString();
    static String currentSystemStateString();
    static inline void setDistanceToGround(float distance) {
        distanceToGround = distance;
    }

    static inline float getDistanceToGround() {
        return distanceToGround;
    }

    static inline void addDistanceToGround(float distance) {
        distanceToGround += distance;
    }

    static inline void subtractDistanceToGround(float distance) {
        distanceToGround -= distance;
    }

    static inline void setTemperatureInside(float temperature) {
        temperatureInside = temperature;
    }

    static inline float getTemperatureInside() {
        return temperatureInside;
    }

    static inline void setDistanceFromHangar(float distance) {
        distanceFromHangar = distance;
    }

    static inline float getDistanceFromHangar() {
        return distanceFromHangar;
    }

    static inline void setSingleDistance(float distance) {
        singleDistance = distance;
    }

    static inline float getSingleDistance() {
        return singleDistance;
    }
};

/* ---- ENUM FOR THE HARDWARE ---- */

typedef enum
{
    LED,
    BUTTON,
    LCD,
    S_DDD,
    S_PIR,
    S_TEMP,
    SERVO_MOTOR
} HardwareType;

inline bool matchHardwareType(HardwareType t1, HardwareType t2)
{
    return (t1 == t2);
}

inline bool isNotHardwareType(HardwareType t1, HardwareType t2)
{
    return (t1 != t2);
}

bool matchHardwareType(HardwareType t1, String t2);

bool isNotHardwareType(HardwareType t1, String t2);

/* ---- ENUM FOR THE TASKS ---- */

typedef enum
{
    T_INPUTOUTPUT,
    T_TAKEOFF,
    T_LANDING,
    T_LEDINACTION,
    T_CHECK_INSIDE_TEMPERATURE,
    T_DOOR
} TaskType;

inline bool matchTaskType(TaskType t1, TaskType t2)
{
    return (t1 == t2);
}

inline bool isNotTaskType(TaskType t1, TaskType t2)
{
    return (t1 != t2);
}

bool matchTaskType(TaskType t1, String t2);

bool isNotTaskType(TaskType t1, String t2);

#endif