#include "FakeTask.h"

FakeTask::FakeTask(TaskType t) : count(0), type(t) { }

void FakeTask::init(int period) {
    Task::init(period);
    count = 0;
}

void FakeTask::tick() {
    count++;
}

TaskType FakeTask::getType() {
    return type;
}

void FakeTask::reset() {
    count = 0;
    timeElapsed = 0;
}