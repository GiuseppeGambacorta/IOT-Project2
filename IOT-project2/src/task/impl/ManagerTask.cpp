#include "task/api/ManagerTask.h"

ManagerTask::ManagerTask(Sonar levelDetector,
                        TemperatureSensor tempSensor,
                        Pir userDetector, 
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

    int level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();
    bool user = userDetector.isDetected();

    if (level>LEVEL_MAX) {
        for (int i = 0; i < MAX_TASKS; i++) {
            taskList[i]->setActive(false);
            if (taskList[i]->getType() == ALLARM_LEVEL
                || taskList[i]->getType() == MANAGER) {
                taskList[i]->setActive(true);
            }
        }
    }
    if (temp>TEMP_MAX) { // TODO : deve rimanere in questo stato per n sec prima di attivare l'allarme
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

