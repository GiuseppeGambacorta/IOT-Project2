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
}

void AlarmTempTask::tick() {
    switch (this->state)
    {
    case IDLE:
        this->timer->active(tempSensor.isThresholdExceeded());
        if (this->timer->isTimeElapsed()) {
            this->state = ALARM;
            //alarmTemp=true;
        }
        break;
    case ALARM:
        display.on();
        display.write("PROBLEM DETECTED");
        ledGreen.turnOff();
        ledRed.turnOn();
        if (door.isOpened()) {
            door.close();
            door.update();
        }
        this->state = RESET;
        //alarmTempReset=true;
        //alarmTemp=false;
        break;
    case RESET:
        ledGreen.turnOn();
        ledRed.turnOff();
        display.clear();
        this->timer->reset();
        this->state = IDLE;
        //alarmTempReset=false;
        break;
    default:
        break;
    }
}

void AlarmTempTask::reset() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    this->timer->reset();
    this->state = IDLE;
    //alarmTempReset=false;
    //alarmTemp=false;
}