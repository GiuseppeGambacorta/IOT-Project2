#include "task/api/ManagerTask.h"

ManagerTask::ManagerTask(AnalogInput levelDetector,
                         AnalogInput tempSensor,
                         DigitalInput userDetector, 
                         Task* taskList[MAX_TASKS])
    : levelDetector(levelDetector),
      tempSensor(tempSensor), 
      userDetector(userDetector) {
    this->type = MANAGER;
    for (int i = 0; i < MAX_TASKS; i++) {
        this->taskList[i] = taskList[i];
    }
}

void ManagerTask::tick() {

    levelDetector.update();
    tempSensor.update();
    userDetector.update();

    int level = levelDetector.getValue();
    int temp = tempSensor.getValue();
    bool user = userDetector.isActive();

    if (level>LEVEL_MAX) {
        for (int i = 0; i < MAX_TASKS; i++) {
            taskList[i]->setActive(false);
            if (taskList[i]->getType() == ALLARM_LEVEL
                || taskList[i]->getType() == MANAGER) {
                taskList[i]->setActive(true);
            }
        }
    }
    if (temp>TEMP_MAX) {
        for (int i = 0; i < MAX_TASKS; i++) {
            taskList[i]->setActive(false);
            if (taskList[i]->getType() == ALLARM_TMP
                || taskList[i]->getType() == MANAGER) {
                taskList[i]->setActive(true);
            }
        }
    } else if (!user) {
        for (int i = 0; i < MAX_TASKS; i++) {
            taskList[i]->setActive(false);
            if (taskList[i]->getType() == SLEEP
                || taskList[i]->getType() == MANAGER) {
                taskList[i]->setActive(true);
            }
        }
    } else {
        for (int i = 0; i < MAX_TASKS; i++) {
            taskList[i]->setActive(false);
            if (taskList[i]->getType() == STD_EXEC
                || taskList[i]->getType() == MANAGER) {
                taskList[i]->setActive(true);
            }
        }
    }
}

