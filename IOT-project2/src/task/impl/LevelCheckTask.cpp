#include "task/api/LevelCheckTask.h"
#include "../../Components/Sonar/api/Sonar.h"
#include <Arduino.h>

LevelCheckTask::LevelCheckTask(Sonar& sensor) : sonar(sensor) {
    state = OK;
}

void LevelCheckTask::tick() {
    if (sonar.isThresholdLower()) {
        state = HIGH_LEVEL;
    } else {
        state = OK;
    }
}

void LevelCheckTask::reset() {
    state = OK;
}

int LevelCheckTask::getState() {
    return state;
}