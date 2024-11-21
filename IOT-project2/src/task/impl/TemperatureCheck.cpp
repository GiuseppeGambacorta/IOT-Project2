#include "task/api/TemperatureCheck.h"
#include "Arduino.h"

#define MAXTEMPTIME 10000

TemperatureCheck::TemperatureCheck(int pin, int threshold) {
    this->pin = pin;
    this->sensor = new TemperatureSensor(pin, threshold);
    state = OK;
}

void TemperatureCheck::tick() {
    if (sensor->isThresholdExceeded()) {
        state = HIGH_TEMP;
    } else {
        state = OK;
    }
}

void TemperatureCheck::reset() {
    state = OK;
}