#include "task/api/TemperatureCheckTask.h"
#include "Arduino.h"

#define MAXTEMPTIME 10000

TemperatureCheckTask::TemperatureCheckTask(int pin) {
    this->pin = pin;
    this->sensor = new TemperatureSensor(pin);
    state = OK;
}

void TemperatureCheckTask::tick() {
    if (sensor->isThresholdExceeded()) {
        state = HIGH_TEMP;
    } else {
        state = OK;
    }
}

void TemperatureCheckTask::reset() {
    state = OK;
}