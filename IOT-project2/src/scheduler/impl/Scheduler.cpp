#include "scheduler/api/Scheduler.h"

Scheduler::Scheduler() {}

void Scheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  this->nTasks = 0;
  this->timer.setupPeriod(basePeriod);
}

bool Scheduler::addInputTask(InputTask* inputTask) {
  this->inputTask = inputTask;
  return true;
}

bool Scheduler::addManagerTask(WasteDisposalTask* managerTask) {
  this->managerTask = managerTask;
  return true;
}

bool Scheduler::addTask(Task* task) {
  if (nTasks < MAX_TASKS) {
    taskExchangeableList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

bool Scheduler::addOutputTask(OutputTask* outputTask) {
  this->outputTask = outputTask;
  return true;
}

void Scheduler::schedule() {
  timer.waitForNextTick();
  inputTask->tick();
  managerTask->tick();
  for (int i = 0; i < nTasks; i++) {
    if (taskExchangeableList[i]->updateAndCheckTime(basePeriod) 
      && taskExchangeableList[i]->isActive()) {
      taskExchangeableList[i]->tick();
    }
  }
  outputTask->tick();
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