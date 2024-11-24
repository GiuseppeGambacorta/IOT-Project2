#include "task/api/UserDetectionTask.h"
#include "task/api/Pir.h"
#include <Arduino.h>

UserDetectionTask::UserDetectionTask(Pir& sensor) : pir(sensor) {
    state = NO_USER;
}

void UserDetectionTask::tick() {
    if (pir.isDetected()) {
        state = USER_DETECTED;
    } else {
        state = NO_USER;
    }
}

void UserDetectionTask::reset() {
    state = NO_USER;
}

int UserDetectionTask::getState() {
    return state;
}