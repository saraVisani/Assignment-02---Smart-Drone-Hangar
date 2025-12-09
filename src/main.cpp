#include "../lib/Configuration/Includes.h"

Scheduler scheduler;

void setup() {
  Hardware::initAllHardware();
  scheduler.init(100);
  Task* ioTask = new InputOutput();
  ioTask->init(20);
  scheduler.addTask(ioTask);
  Task* tempTask = new CheckInsideTemperature();
  tempTask->init(50);
  scheduler.addTask(tempTask);
}

void loop() {
  scheduler.schedule();
}