#ifndef __FAKESPIR__
#define __FAKESPIR__

#include "./Util/Hardware/Api/ISpir.h"

class FakeSpir : public ISpir {
    private:
    bool stateOn = false;

    public:
        void init(int pin = 0) override;
        bool isDroneDetected() const override;
        void printDebug() const override;
};

#endif