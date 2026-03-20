#ifndef __FAKELCD__
#define __FAKELCD__

#include "./Util/Hardware/Api/ILcd.h"

class FakeLcd : public ILcd {
private:
    bool cleared = false;
    String line1 = "";
    String line2 = "";

public:
    void init(int pin = 0) override;

    void printLine(const char* message, int line = 0) override;
    void print(const char* message0, const char* message1) override;
    void printLine(const String& message, int line = 0) override {
        printLine(message.c_str(), line);
    }
    void print(const String& message0, const String& message1) override {
        print(message0.c_str(), message1.c_str());
    }

    void clear() override;
    void clearLine(int line = 0) override;

    void activateClearFlag() override {
        cleared = false;
    }

    void on() override {}
    void off() override {}

    // 🔥 TEST HELPERS
    bool isCleared() const { return cleared; }
    String getLine1() const { return line1; }
    String getLine2() const { return line2; }
};

#endif