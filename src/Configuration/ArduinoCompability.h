#ifndef ARDUINO_COMPATIBILITY_H
#define ARDUINO_COMPATIBILITY_H

#ifdef ARDUINO

    #include <Arduino.h>

#else

    #include <string>
    #include <sstream>
    #include <chrono>
    #include <iostream>
    #include <cctype>
    #include <cstring>

    typedef bool boolean;

    // =============================
    // Arduino-like String wrapper
    // =============================
    struct String : public std::string {
        using std::string::string;

        String() : std::string() {}
        String(const std::string& s) : std::string(s) {}
        String(std::string&& s) : std::string(std::move(s)) {}

        String(float v) {
            std::ostringstream oss;
            oss << v;
            assign(oss.str());
        }

        String(double v) : String(static_cast<float>(v)) {}

        String(int v) {
            std::ostringstream oss;
            oss << v;
            assign(oss.str());
        }

        String(unsigned int v) {
            std::ostringstream oss;
            oss << v;
            assign(oss.str());
        }

        String(unsigned long v) {
            std::ostringstream oss;
            oss << v;
            assign(oss.str());
        }

        String(long v) {
            std::ostringstream oss;
            oss << v;
            assign(oss.str());
        }

        void trim() {
            const char* whitespace = " \t\n\r";
            size_t start = find_first_not_of(whitespace);
            size_t end = find_last_not_of(whitespace);

            if (start == std::string::npos) {
                clear();
            } else {
                *this = substr(start, end - start + 1);
            }
        }
    };

    // =============================
    // Serial mock
    // =============================
    class SerialMock {
    public:
        void begin(int) {}
        void setTimeout(int) {}
        int available() { return 0; }

        String readStringUntil(char) {
            return String("");
        }

        void print(const String& s) { std::cout << s; }
        void print(const char* s) { std::cout << s; }

        void println(const String& s) { std::cout << s << std::endl; }
        void println(const char* s) { std::cout << s << std::endl; }
    };

    static SerialMock Serial;

    // =============================
    // millis()
    // =============================
    extern unsigned long fakeMillis;

    inline unsigned long millis() {
        return fakeMillis;
    }

    inline void advanceMillis(unsigned long ms) {
        fakeMillis += ms;
    }

    inline void resetMillis() {
        fakeMillis = 0;
    }

    // =============================
    // strcasecmp
    // =============================
    inline int strcasecmp(const char* a, const char* b) {
        while (*a && *b) {
            char ca = std::tolower(*a);
            char cb = std::tolower(*b);
            if (ca != cb) return ca - cb;
            ++a; ++b;
        }
        return *a - *b;
    }

#endif

#endif
