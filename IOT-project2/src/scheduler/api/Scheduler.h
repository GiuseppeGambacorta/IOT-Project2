#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "ArduinoStandardLibrary.h"

#include "task/api/Task.h"
#include "task/api/InputTask.h"
#include "task/api/ManagerTask.h"
#include "task/api/OutputTask.h"

#define MAX_TASKS 10

class Scheduler {

private: 
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  SchedulerTimer timer = SchedulerTimer();

public:
  Scheduler();
  void init(int basePeriod); 
  bool addTask(Task* task); 
  void schedule();
  void reset();
};

#endif