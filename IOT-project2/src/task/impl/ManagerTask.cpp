#include "task/api/ManagerTask.h"

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
        if (taskList[i]->getType() == ALLARM_LEVEL) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else if (tempAlarm) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == ALLARM_TMP) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else if (!userStatus) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == SLEEP) {
          taskList[i]->setActive(true);
        }
      }
    }
  } else {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskList[i] != nullptr) {
        taskList[i]->setActive(false);
        if (taskList[i]->getType() == STD_EXEC) {
          taskList[i]->setActive(true);
        }
      }
    }
  }
}

void ManagerTask::reset() {
  tempAlarm = false;
  levelAlarm = false;
  userStatus = true;
  tempTimer = new Timer(MAXTEMPTIME);
  userTimer = new Timer(TSleep);
}