#include "InputOutput.h"

inline bool InputOutput::isHangarAvailable() {
    return State::matchSystemState(OK) && (State::matchDroneState(OPERATING) || State::matchDroneState(IDLE));
}

void InputOutput::read() {
    while(Serial.available()) {
        String incoming = Serial.readStringUntil('\n');
        incoming.trim();

        if(strcasecmp(incoming.c_str(), "logs") == 0) {
            logs();
            return;
        }

        // Decode and process the incoming message
        if(isHangarAvailable()) {
            if(strcasecmp(incoming.c_str(), "take off") == 0 && State::matchDroneState(IDLE)){
                State::setDroneState(TAKEOFF);
            } else if (strcasecmp(incoming.c_str(), "landing") == 0 && State::matchDroneState(OPERATING)){
                State::setDroneState(LANDING);
            }
        } else {
            // Ignore commands if hangar is not available
            if(State::isNotSystemState(OK)){
                String message = "System state is " + State::currentSystemStateString() + ". Command ignored.";
                Serial.println(message);
            } else {
                Serial.println("Hangar not available. Command ignored.");
            }
        }
    }
}

void InputOutput::send() {
    /**
     * Status message format:
     *  /n to indicate the start of a new message
     *  - separators between fields
     */
    String statusMessage = State::currentSystemStateString() + "-" + State::currentDroneStateString();
    if (State::matchDroneState(LANDING)) {
        statusMessage += "-" + String(State::getDistanceToGround());
    }
    /**
     * For logs porpuses saved in a different way in java application.
     * They must begin by *
     */
    statusMessage = "-*-" + String(State::getTemperatureInside()) + "-";
    if(State::matchDroneState(TAKEOFF)){
        statusMessage += String(State::getDistanceFromHangar());
    } else {
        statusMessage += "N/A";
    }

    Serial.println(statusMessage);
}

void InputOutput::logs()
{
    /**
     * Log message format:
     *  * to indicate the start of a log message
     *  - separators between fields
     */
    String statusMessage = "*-" + State::currentSystemStateString() + "-" + State::currentDroneStateString();
    statusMessage += "-" + String(State::getTemperatureInside()) + "-";
    if(State::matchDroneState(TAKEOFF)){
        statusMessage += String(State::getDistanceFromHangar()) + "-";
    } else {
        statusMessage += "N/A-";
    }
    if(State::matchDroneState(LANDING)) {
        statusMessage += String(State::getDistanceToGround());
    } else {
        statusMessage += "N/A";
    }
    Serial.println(statusMessage);
}

void InputOutput::tick() {
    read();
    send();
}