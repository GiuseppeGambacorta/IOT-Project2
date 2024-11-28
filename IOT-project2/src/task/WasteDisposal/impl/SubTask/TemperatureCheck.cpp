#include "../../api/subTask/TemperatureCheck.h"
#include <Arduino.h>

#define MAXTEMPTIME 10000

TemperatureCheck::TemperatureCheck(TemperatureSensor& sensor) : tempSensor(sensor) {
    state = OK;
    timer = new Timer(MAXTEMPTIME);
}

void TemperatureCheck::tick() {
    timer->active(tempSensor.isThresholdExceeded());
    if (timer->isTimeElapsed()) {
        state = EMERGENCY;
    } else {
        state = OK;
    }

}

void TemperatureCheck::reset() {
    state = OK;
    timer->reset();
}

int TemperatureCheck::getState() {
    return state;
}