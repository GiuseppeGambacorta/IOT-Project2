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
  InputTask* inputTask;
  ManagerTask* managerTask;
  Task* taskExchangeableList[MAX_TASKS];  
  OutputTask* outputTask;
  SchedulerTimer timer = SchedulerTimer();

public:
  Scheduler();
  void init(int basePeriod); 
  bool addInputTask(InputTask* inputTask);
  bool addManagerTask(ManagerTask* managerTask); 
  bool addTask(Task* task); 
  bool addOutputTask(OutputTask* outputTask); 
  void schedule();
  Task** getTaskList();
  int getNumTask();
  Task* getTask(int index);
};

#endif