#ifndef __LEDINACTION__
#define __LEDINACTION__

#include "Task.h"

class LedInAction: public Task{
    private:
    unsigned long lastBlink;

    public:
    void init(int period) override{
        Task::init(period);
        lastBlink = 0;
    }
    void checkChange();
    void blinking();
    void tick() override;
    inline TaskType getType() override;
};
#endif