#ifndef __LCD__
#define __LCD__

#include "./Hardware/Component.h"
#include <./Libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h>

class Lcd : public Component {
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
        boolean cleared = false, p_1 = false, p_2 = false;
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::LCD;
        }
        void printLine(const char* message, int line = 0);
        inline void printLine(const String& message, int line = 0) {
            printLine(message.c_str(), line);
        }
        void print(const char* message0, const char* message1) {
            printLine(message0, 0);
            printLine(message1, 1);
        }
        void print(const String& message0, const String& message1) {
            printLine(message0.c_str(), 0);
            printLine(message1.c_str(), 1);
        }
        inline void clear();
        void clearLine(int line = 0);
        inline void on();
        inline void off();
        inline void activateClearFlag() {
            cleared = false;
        }
};

#endif