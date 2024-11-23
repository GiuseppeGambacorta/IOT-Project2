#include "scheduler/api/Scheduler.h"

void Scheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  this->nExechangeableTasks = 0;
  this->timer.setupPeriod(basePeriod);
  // task di input
  managerTask = ManagerTask();
  // task di output
}

bool Scheduler::addTask(Task* task) {
  if (nExechangeableTasks < MAX_EXCHANGEABLE_TASKS) {
    taskExchangeableList[nExechangeableTasks] = task;
    nExechangeableTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule() {
  timer.waitForNextTick();
  // task di input
  managerTask.tick();
  for (int i = 0; i < nExechangeableTasks; i++) {
    if (taskExchangeableList[i]->updateAndCheckTime(basePeriod) && taskExchangeableList[i]->isActive()) {
      taskExchangeableList[i]->tick();
    }
  }
  // task di output
}