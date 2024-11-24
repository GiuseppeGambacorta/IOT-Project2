#include "task/api/ManagerTask.h"

#define IS_ESSENTIAL_TASK taskList[i]->getType() == IN || taskList[i]->getType() == MANAGER

ManagerTask::ManagerTask(Sonar& levelDetector,
                         TemperatureSensor& tempSensor,
                         Pir& userDetector,
                         Task* taskList[MAX_TASKS])
    : levelDetector(levelDetector),
      tempSensor(tempSensor), 
      userDetector(userDetector) {
  for (int i = 0; i < MAX_TASKS; i++) {
    this->taskList[i] = taskList[i];
  }
}

void ManagerTask::tick() {

  int level = levelDetector.readDistance();
  int temp = tempSensor.readTemperature();
  bool user = userDetector.isDetected();

  if (level > LEVEL_MAX) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == ALLARM_LEVEL || IS_ESSENTIAL_TASK) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else if (temp > TEMP_MAX) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == ALLARM_TMP || IS_ESSENTIAL_TASK) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else if (!user) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == SLEEP || IS_ESSENTIAL_TASK) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == STD_EXEC || IS_ESSENTIAL_TASK) {
          taskList[i]->setActive(true);
        }
      }
    }
  }
}