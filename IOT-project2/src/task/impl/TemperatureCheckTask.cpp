#include "task/api/TemperatureCheckTask.h"
#include "../../Components/TemperatureSensor/api/TemperatureSensor.h"
#include <Arduino.h>

#define MAXTEMPTIME 10000

TemperatureCheckTask::TemperatureCheckTask(TemperatureSensor& sensor) : tempSensor(sensor) {
    state = OK;
    timer = new Timer(MAXTEMPTIME);
}

void TemperatureCheckTask::tick() {
    timer->active(tempSensor.isThresholdExceeded());
    if (timer->isTimeElapsed()) {
        state = EMERGENCY;
    } else {
        state = OK;
    }

}

void TemperatureCheckTask::reset() {
    state = OK;
    timer->reset();
}

int TemperatureCheckTask::getState() {
    return state;
}