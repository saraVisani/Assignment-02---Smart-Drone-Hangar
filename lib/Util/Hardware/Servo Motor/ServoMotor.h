#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include "./Hardware/Component.h"
#include <./Libraries/ServoTimer2/ServoTimer2.h>

class ServoMotor : public Component {
    private:
        bool closed;
        bool opened;
        int angle;
        ServoTimer2 motor;
        int targetAngle = 0;
        unsigned long lastStepTime = 0;
        int stepDelay = 20;
        int stepSize = 2;
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::SERVO_MOTOR;
        }
        inline bool isClosed();
        inline bool isOpened();
        inline bool greaterThan(int angle);
        inline bool isClosing();
        inline bool isOpening();
        inline bool lessThan(int angle);
        inline int getAngle();
        void close();
        void open();
        void update();
        void setPosition(int angle);
};

#endif