#include "scheduler/api/Scheduler.h"

void Scheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  this->nExechangeableTasks = 0;
  this->timer.setupPeriod(basePeriod);
  managerTask = ManagerTask();
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
  managerTask.tick();
  for (int i = 0; i < nExechangeableTasks; i++) {
    if (taskExchangeableList[i]->updateAndCheckTime(basePeriod)) {
      taskExchangeableList[i]->tick();
    }
  }
}