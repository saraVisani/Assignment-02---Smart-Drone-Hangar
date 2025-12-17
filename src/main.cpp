#include "../lib/Configuration/Includes.h"

Scheduler scheduler;

void setup() {
  Hardware::initAllHardware();
  scheduler.init(200);
  Task* ioTask = new InputOutput();
  ioTask->init(20);
  scheduler.addTask(ioTask);
  Task* tempTask = new CheckInsideTemperature();
  tempTask->init(20);
  scheduler.addTask(tempTask);
  Task* takeOffTask = new TakeOff();
  takeOffTask->init(40);
  scheduler.addTask(takeOffTask);
  Task* landing = new Landing();
  landing->init(40);
  scheduler.addTask(landing);
  Task* ledTask = new LedInAction();
  ledTask->init(10);
  scheduler.addTask(ledTask);
  Task* doorTask = new Door();
  doorTask->init(10);
  scheduler.addTask(doorTask);
}

void loop() {
  scheduler.schedule();
}