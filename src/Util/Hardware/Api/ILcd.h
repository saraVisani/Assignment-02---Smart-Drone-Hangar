#ifndef __ILCD__
#define __ILCD__

#include "./Util/Hardware/Component.h"

class ILcd : public Component {
    public:
        inline HardwareType getType() override {
            return HardwareType::LCD;
        }
        virtual void printLine(const char* message, int line = 0) = 0;
        virtual void printLine(const String& message, int line = 0) = 0;
        virtual void print(const char* message0, const char* message1) = 0;
        virtual void print(const String& message0, const String& message1) = 0;
        virtual void clear() = 0;
        virtual void clearLine(int line = 0) = 0;
        virtual void on() = 0;
        virtual void off() = 0;
        virtual void activateClearFlag() = 0;
};

#endif