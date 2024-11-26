#include "task/api/ManagerTask.h"

void ManagerTask::tick() {
    int level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();
    bool user = userDetector.isDetected();

    // Gestione degli allarmi e degli stati
    if (level < LEVEL_MAX) {
        levelAlarm = true;
    } else {
        levelAlarm = false;
    }

    tempTimer.active(temp > TEMP_MAX);
    if (tempTimer.isTimeElapsed()) {
        tempAlarm = true;
    } else {
        tempAlarm = false;
    }

    userTimer.active(user);
    if (userTimer.isTimeElapsed()) {
        userStatus = false;
    } else {
        userStatus = true;
    }

    // Selezione del task attivo
    TaskType activeTaskType = STD_EXEC; // Default task

    if (levelAlarm) {
        activeTaskType = ALLARM_LEVEL;
    } else if (tempAlarm) {
        activeTaskType = ALLARM_TMP;
    } else if (!userStatus) {
        activeTaskType = SLEEP;
    }

    // Attivazione del task corrispondente
    for (int i = 0; i < MAX_TASKS; i++) {
        if (taskList[i] != nullptr) {
            taskList[i]->setActive(taskList[i]->getType() == activeTaskType);
        }
    }
}

void ManagerTask::reset() {
    tempAlarm = false;
    levelAlarm = false;
    userStatus = true;

    tempTimer.reset();
    userTimer.reset();
}
