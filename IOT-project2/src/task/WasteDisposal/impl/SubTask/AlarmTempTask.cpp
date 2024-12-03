#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmTempTask.h"
#include "Components/Display/Api/Display.h"

#define MAXTEMPTIME 10000

AlarmTempTask::AlarmTempTask(DigitalOutput& ledGreen,
                               DigitalOutput& ledRed,
                               Display& display,
                               Door& door,
                               TemperatureSensor& tempSensor) 
                               : ledGreen(ledGreen), ledRed(ledRed),
                                 display(display), door(door),
                                 tempSensor(tempSensor) {
    this->timer = new Timer(MAXTEMPTIME);
    this->state = IDLE;
    fire = ServiceLocator::getSerialManagerInstance().getvar(0);
}

void AlarmTempTask::tick() {
    switch (this->state) {
    case IDLE:
        handleIdleState();
        break;
    case ALARM:
        handleAlarmState();
        break;
    case RESET:
        handleResetState();
        break;
    default:
        break;
    }
}

void AlarmTempTask::handleIdleState() {/*
    this->timer->active(tempSensor.isThresholdExceeded());
    if (this->timer->isTimeElapsed()) {
        this->state = ALARM;
    }*/
   this->state = ALARM;
}

void AlarmTempTask::handleAlarmState() {
    display.on();
    display.write("PROBLEM DETECTED");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
        door.update();
    }
     int temp = tempSensor.readTemperature();
      ServiceLocator::getSerialManagerInstance().addEventMessage("Temperature alarm");
    if(*fire == 1 && temp < 100){
        this->state = RESET;
    }  else
    {
         ServiceLocator::getSerialManagerInstance().addEventMessage("un cazz");
    }
}

void AlarmTempTask::handleResetState() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    this->timer->reset();
    *fire = 2;
    this->state = IDLE;
    ServiceLocator::getSerialManagerInstance().addEventMessage("Temperature alarm reset");
}

void AlarmTempTask::reset() {

    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    this->timer->reset();
    *fire = 0;
    this->state = IDLE;
}