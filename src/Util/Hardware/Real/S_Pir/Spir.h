#ifndef __SPIR__
#define __SPIR__

#include "./Util/Hardware/Api/ISpir.h"

class Spir : public ISpir {
    private:
        bool stateOn = false;

    public:
        void init(int pin = 0) override;
        bool isDroneDetected() const override;
        void printDebug() const override;
};

#endif