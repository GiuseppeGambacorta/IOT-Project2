#include "scheduler/api/Scheduler.h"

Scheduler::Scheduler() {}

void Scheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  this->nTasks = 0;
  this->timer.setupPeriod(basePeriod);
}

bool Scheduler::addTask(Task* task) {
  if (task->getType() == IN) {
    this->inputTask = &task;
  }
  if (task->getType() == MANAGER) {
    this->managerTask = &task;
  }
  if (nTasks < MAX_TASKS) {
    taskExchangeableList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule() {
  timer.waitForNextTick();
  inputTask.tick();
  managerTask.tick();
  for (int i = 0; i < nTasks; i++) {
    if (taskExchangeableList[i]->updateAndCheckTime(basePeriod) 
      && taskExchangeableList[i]->isActive()) {
      taskExchangeableList[i]->tick();
    }
  }
}

Task** Scheduler::getTaskList(){
  Task** retTaskList;
  return retTaskList = this->taskExchangeableList;
}

int Scheduler::getNumTask(){
  int retNumTask;
  return retNumTask= this->nTasks;
}

Task* Scheduler::getTask(int index){
  Task* retTask;
  return retTask = this->taskExchangeableList[index];
}