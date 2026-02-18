#ifndef __FAKE_TIMER__
#define __FAKE_TIMER__

#include "./Timer/Timer.h"

/**
 * FakeTimer simula un Timer senza dipendere dall'hardware.
 * Utile per test e simulazioni.
 */
class FakeTimer : public Timer {
private:
    unsigned long currentTick;

public:
    FakeTimer() : currentTick(0) {}

    /**
     * Simula la configurazione del periodo.
     * @param periodMs Periodo in millisecondi
     */
    void setupPeriod(int periodMs) override {
        // Non fa nulla, è solo simulazione
        currentTick = 0;
    }

    /**
     * Simula l'attesa del prossimo tick.
     * Incrementa il contatore interno invece di bloccare.
     */
    void waitForNextTick() override {
        currentTick++;
    }

    /**
     * Permette di leggere il "tick" corrente del timer
     */
    unsigned long getCurrentTick() const {
        return currentTick;
    }

    /**
     * Permette di avanzare manualmente il timer di N tick
     */
    void advanceTicks(unsigned long n) {
        currentTick += n;
    }
};

#endif
