#ifndef __LCD__
#define __LCD__

#include "./Util/Hardware/Api/ILcd.h"
#include "./Util/Libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

class Lcd : public ILcd {
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
        boolean cleared = false, p_1 = false, p_2 = false;
    public:
        void init(int pin = 0) override;
        void printLine(const char* message, int line = 0) override;
        inline void printLine(const String& message, int line = 0)  override {
            printLine(message.c_str(), line);
        }
        void print(const char* message0, const char* message1)  override {
            printLine(message0, 0);
            printLine(message1, 1);
        }
        void print(const String& message0, const String& message1)  override {
            printLine(message0.c_str(), 0);
            printLine(message1.c_str(), 1);
        }
        void clear() override;
        void clearLine(int line = 0) override;
        inline void on()  override {
            lcd.display();
        }
        inline void off()  override {
            lcd.noDisplay();
        }
        inline void activateClearFlag() override {
            cleared = false;
        }
};

#endif