#include "task/api/ManagerTask.h"

#define IS_ESSENTIAL_TASK taskList[i]->getType() == IN || taskList[i]->getType() == MANAGER
#define MAXTEMPTIME 10000

ManagerTask::ManagerTask(Sonar& levelDetector,
                         TemperatureSensor& tempSensor,
                         Pir& userDetector,
                         Task* taskList[MAX_TASKS])
    : levelDetector(levelDetector),
      tempSensor(tempSensor), 
      userDetector(userDetector) {
  tempAlarm = false;
  levelAlarm = false;
  userStatus = true;
  tempTimer = new Timer(MAXTEMPTIME);
  userTimer = new Timer(TSleep);
  for (int i = 0; i < MAX_TASKS; i++) {
    this->taskList[i] = taskList[i];
  }
}

void ManagerTask::tick() {

  int level = levelDetector.readDistance();
  int temp = tempSensor.readTemperature();
  bool user = userDetector.isDetected();

  if (level < LEVEL_MAX) {
    levelAlarm = true;
  } else {
    levelAlarm = false;
  }

  tempTimer->active(temp > TEMP_MAX);
  if (tempTimer->isTimeElapsed()) {
    tempAlarm = true;
  } else {
    tempAlarm = false;
  }

  userTimer->active(user);
  if (userTimer->isTimeElapsed()) {
    userStatus = false;
  } else {
    userStatus = true;
  }

  if (levelAlarm) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == ALLARM_LEVEL || IS_ESSENTIAL_TASK) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else if (tempAlarm) {
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