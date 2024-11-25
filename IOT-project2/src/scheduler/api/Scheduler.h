#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "ArduinoStandardLibrary.h"
#include "task/api/Task.h"

#define MAX_TASKS 10

class Scheduler {

private: 
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  SchedulerTimer timer;

public:
  Scheduler();

  void init(int basePeriod);  
  bool addTask(Task* task);  
  void schedule();
  Task** getTaskList();
  int getNumTask();
  Task* getTask(int index);
};

#endif