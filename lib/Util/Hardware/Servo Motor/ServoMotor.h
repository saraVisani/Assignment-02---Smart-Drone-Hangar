#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include "./Hardware/Component.h"

class ServoMotor : public Component {
    private:
        bool closed;
        bool opened;
        int angle;
    public:
        void init(int pin = 0) override;
        inline HardwareType getType() override {
            return HardwareType::SERVO_MOTOR;
        }
        inline bool isClosed();
        inline bool isOpened();
        inline bool greaterThan(int angle);
        inline bool lessThan(int angle);
        inline int getAngle();
        void close();
        void open();
        void setPosition(int angle);
};

#endif