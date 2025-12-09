#include "InputOutput.h"

inline bool InputOutput::isHangarAvailable() {
    return State::matchSystemState(OK) && (State::matchDroneState(OPERATING) || State::matchDroneState(IDLE));
}

void InputOutput::read() {
    while(Serial.available()) {
        String incoming = Serial.readStringUntil('\n');
        incoming.trim();

        // Decode and process the incoming message
        if(isHangarAvailable()) {
            if(strcasecmp(incoming.c_str(), "take off") == 0){
                State::setDroneState(TAKEOFF);
            } else if (strcasecmp(incoming.c_str(), "landing") == 0){
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
    String statusMessage = State::currentSystemStateString() + "-" + State::currentDroneStateString();
    if (State::matchDroneState(LANDING)) {
        statusMessage += "-" + String(State::getDistanceToGround());
    }
    Serial.println(statusMessage);
}

void InputOutput::tick() {
    read();
    send();
}