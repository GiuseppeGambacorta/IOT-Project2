#include "task/api/TemperatureCheck.h"
#include "Arduino.h"

#define MAXTEMPTIME 10000

TemperatureCheckTask::TemperatureCheckTask(int pin, int threshold) {
    this->pin = pin;
    this->sensor = new TemperatureSensor(pin, threshold);
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