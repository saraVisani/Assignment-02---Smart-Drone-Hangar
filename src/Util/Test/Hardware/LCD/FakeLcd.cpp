#include "FakeLcd.h"

void FakeLcd::init(int pin) {
    cleared = false;
    line1 = "";
    line2 = "";
}

void FakeLcd::printLine(const char* message, int line) {
    cleared = false;

    if (line == 0) {
        line1 = message;
    } else if (line == 1) {
        line2 = message;
    }
}

void FakeLcd::print(const char* message0, const char* message1) {
    line1 = message0;
    line2 = message1;
    cleared = false;
}

void FakeLcd::clear() {
    cleared = true;
    line1 = "";
    line2 = "";
}

void FakeLcd::clearLine(int line) {
    if (line == 0) line1 = "";
    if (line == 1) line2 = "";
}