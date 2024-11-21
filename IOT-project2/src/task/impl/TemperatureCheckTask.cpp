#include "task/api/TemperatureCheckTask.h"
#include "task/api/TemperatureSensor.h"
#include <Arduino.h>

#define MAXTEMPTIME 10000

TemperatureCheckTask::TemperatureCheckTask() {
    state = OK;
}

void TemperatureCheckTask::tick(TemperatureSensor& tempSensor) {
    if (tempSensor.isThresholdExceeded()) {
        state = HIGH_TEMP;
    } else {
        state = OK;
    }
}

void TemperatureCheckTask::reset() {
    state = OK;
}