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
    #include <queue>
    #include <vector>

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
        private:
            std::queue<String> inputBuffer;
            std::vector<String> outputBuffer;

        public:
            void begin(int) {}
            void setTimeout(int) {}

            // =============================
            // INPUT SIDE (test-controlled)
            // =============================
            void inject(const String& msg) {
                inputBuffer.push(msg);
            }

            int available() {
                return inputBuffer.empty() ? 0 : 1;
            }

            String readStringUntil(char) {
                if (inputBuffer.empty()) return String("");
                String msg = inputBuffer.front();
                inputBuffer.pop();
                return msg;
            }

            // =============================
            // OUTPUT SIDE
            // =============================
            void print(const String& s) {
                outputBuffer.push_back(s);
            }

            void print(const char* s) {
                outputBuffer.push_back(String(s));
            }

            void println(const String& s) {
                outputBuffer.push_back(s);
            }

            void println(const char* s) {
                outputBuffer.push_back(String(s));
            }

            void printToConsole(const String& s) {
                std::cout << s << std::endl;
            }

            // =============================
            // TEST HELPERS
            // =============================
            const std::vector<String>& getOutput() const {
                return outputBuffer;
            }

            String getLastOutput() const {
                if (outputBuffer.empty()) return "";
                return outputBuffer.back();
            }

            void clear() {
                while (!inputBuffer.empty()) inputBuffer.pop();
                outputBuffer.clear();
            }

            bool serialContains(const std::string& substring) const {
                for(const auto& line : outputBuffer) {
                    if(line.find(substring) != std::string::npos) return true;
                }
                return false;
            }
        };

    extern SerialMock Serial;

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
