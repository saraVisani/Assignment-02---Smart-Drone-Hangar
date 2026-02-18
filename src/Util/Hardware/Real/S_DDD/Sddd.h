#ifndef __SDDD__
#define __SDDD__

#include "./Util/Hardware/Api/ISddd.h"

class Sddd : public ISddd {
    private:
        float lastDistance = 0;
        int count = 0;
    public:
        void init(int pin = 0) override;
        float readDistance() override;
        bool readDistanceAvarage(float &avarage, int samples = 5) override;
        bool isDroneInside() const override;
        bool isDroneOutside() const override;
        void printDistanceDebug() const override;

};

#endif