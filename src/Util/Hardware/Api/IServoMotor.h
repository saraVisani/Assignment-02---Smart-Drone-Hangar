#ifndef __ISERVOMOTOR__
#define __ISERVOMOTOR__

#include "./Util/Hardware/Component.h"

class IServoMotor : public Component {
    public:
        inline HardwareType getType() override {
            return HardwareType::SERVO_MOTOR;
        }
        virtual bool greaterThan(int angle) const = 0;
        virtual bool lessThan(int angle) const = 0;
        virtual bool isClosed() const = 0;
        virtual bool isOpened() const = 0;
        virtual bool isClosing() const = 0;
        virtual bool isOpening() const = 0;
        virtual int getAngle() const = 0;
        virtual void close() = 0;
        virtual void open() = 0;
        virtual void update() = 0;
        virtual void setPosition(int angle) = 0;
};

#endif