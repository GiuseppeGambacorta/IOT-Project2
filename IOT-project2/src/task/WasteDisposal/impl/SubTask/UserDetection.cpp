#include "task/api/UserDetection.h"
#include "../../Components/Pir/api/Pir.h"
#include <Arduino.h>

UserDetection::UserDetection(Pir& sensor) : pir(sensor) {
    state = NO_USER;
}

void UserDetection::tick() {
    if (pir.isDetected()) {
        state = USER_DETECTED;
    } else {
        state = NO_USER;
    }
}

void UserDetection::reset() {
    state = NO_USER;
}

int UserDetection::getState() {
    return state;
}