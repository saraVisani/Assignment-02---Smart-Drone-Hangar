#ifndef __FAKELCD__
#define __FAKELCD__

#include "./Util/Hardware/Api/ILcd.h"

class FakeLcd : public ILcd {
    private:
        boolean cleared = false, p_1 = false, p_2 = false;
    public:
        void init(int pin = 0) override;
        void printLine(const char* message, int line = 0) override;
        inline void printLine(const String& message, int line = 0) override {
            //printLine(message.c_str(), line);
        }
        void print(const char* message0, const char* message1) override {
            //printLine(message0, 0);
            //printLine(message1, 1);
        }
        void print(const String& message0, const String& message1) override {
            //printLine(message0.c_str(), 0);
            //printLine(message1.c_str(), 1);
        }
        inline void activateClearFlag() override {
            cleared = false;
        }
        void clear() override;
        void clearLine(int line = 0) override;
        inline void on() override {
            //lcd.display();
        }
        inline void off() override {
            //lcd.noDisplay();
        }
};

#endif