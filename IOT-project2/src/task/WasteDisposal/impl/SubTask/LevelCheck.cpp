#include "../../api/subTask/LevelCheck.h"
#include <Arduino.h>

LevelCheck::LevelCheck(Sonar& sensor) : sonar(sensor) {
    state = OK;
}

void LevelCheck::tick() {
    if (sonar.isThresholdLower()) {
        state = HIGH_LEVEL;
    } else {
        state = OK;
    }
}

void LevelCheck::reset() {
    state = OK;
}

int LevelCheck::getState() {
    return state;
}