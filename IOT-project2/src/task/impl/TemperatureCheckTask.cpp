#include "task/api/TemperatureCheckTask.h"
#include "task/api/TemperatureSensor.h"
#include <Arduino.h>

#define MAXTEMPTIME 10000

TemperatureCheckTask::TemperatureCheckTask(TemperatureSensor& sensor) : tempSensor(sensor) {
    state = OK;
    highTempStartTime = 0;
}

void TemperatureCheckTask::tick() {
    if (tempSensor.isThresholdExceeded()) {
        if (state == OK) {
            highTempStartTime = millis(); // Start the timer
            state = HIGH_TEMP;
        } else if (state == HIGH_TEMP && millis() - highTempStartTime >= MAXTEMPTIME) {
            state = EMERGENCY;
        }
    } else {
        state = OK;
        highTempStartTime = 0; // Reset the timer
    }
}

void TemperatureCheckTask::reset() {
    state = OK;
    highTempStartTime = 0;
}