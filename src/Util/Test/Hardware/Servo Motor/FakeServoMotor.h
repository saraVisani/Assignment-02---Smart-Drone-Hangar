#ifndef __FAKESERVOMOTOR__
#define __FAKESERVOMOTOR__

#include "./Util/Hardware/Api/IServoMotor.h"

class FakeServoMotor : public IServoMotor {
    private:
        bool closed;
        bool opened;
        int angle;
        int targetAngle = 0;
        unsigned long lastStepTime = 0;
        unsigned int stepDelay = 20;
        int stepSize = 2;

    public:
        void init(int pin = 0) override;
        inline bool isClosed() const override {
            return closed;
        }
        inline bool isOpened() const override {
            return opened;
        }
        inline bool greaterThan(int angle) const override {
            return angle > this->angle;
        }
        inline bool lessThan(int angle) const override {
            return angle < this->angle;
        }
        inline bool isClosing() const override {
            return !isClosed() && targetAngle == 0;
        }
        inline bool isOpening() const override {
            return !isOpened() && targetAngle == 180;
        }
        inline int getAngle() const override {
            return angle;
        }
        void close() override;
        void open() override;
        void update() override;
        void setPosition(int angle) override;
};

#endif