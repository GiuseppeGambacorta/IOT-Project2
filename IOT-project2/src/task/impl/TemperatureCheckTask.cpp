#include "task/api/TemperatureCheckTask.h"
#include "task/api/TemperatureSensor.h"
#include <Arduino.h>

#define MAXTEMPTIME 10000

TemperatureCheckTask::TemperatureCheckTask(TemperatureSensor& sensor) : tempSensor(sensor) {
    state = OK;
}

void TemperatureCheckTask::tick() {
    if (tempSensor.isThresholdExceeded()) {
        state = HIGH_TEMP;
    } else {
        state = OK;
    }
}

void TemperatureCheckTask::reset() {
    state = OK;
}