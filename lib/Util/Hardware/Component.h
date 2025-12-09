#ifndef __COMPONENT__
#define __COMPONENT__

#include "Arduino.h"
#include "Globals.h"

class Component {
    public:
        virtual void init(int pin = 0) = 0;
        virtual HardwareType getType() = 0;
        inline static bool matchHardwareType(HardwareType state1, HardwareType state2){
            return state1 == state2;
        }
        inline static bool isNotHardwareType(HardwareType state1, HardwareType state2){
            return state1 != state2;
        }
};

#endif