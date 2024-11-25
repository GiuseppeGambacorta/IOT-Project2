#include "scheduler/api/Scheduler.h"

void Scheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  this->nTasks = 0;
  this->timer.setupPeriod(basePeriod);
}

bool Scheduler::addTask(Task* task) {
  if (nTasks < MAX_TASKS) {
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule() {
  timer.waitForNextTick();
  for (int i = 0; i < nTasks; i++) {
    if (taskList[i]->updateAndCheckTime(basePeriod) 
      && taskList[i]->isActive()) {
      taskList[i]->tick();
    }
  }
}

//TODO : get task list

int Scheduler::getNumTask(){
  int retNumTask;
  return retNumTask= this->nTasks;
}

Task* Scheduler::getTask(int index){
  Task* retTask;
  return retTask = this->taskList[index];
}