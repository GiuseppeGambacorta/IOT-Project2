#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmLevelTask.h"
#include "Components/Display/Api/Display.h"

AlarmLevelTask::AlarmLevelTask(Door& door,
                                 Display& display,
                                 DigitalOutput& ledGreen,
                                 DigitalOutput& ledRed,
                                 Sonar& levelDetector) 
                                 : door(door), display(display), ledGreen(ledGreen), ledRed(ledRed), levelDetector(levelDetector) {
    //this->timer = new Timer(MAXTEMPTIME);
    this->state = IDLE;
}

void AlarmLevelTask::tick() {
    switch (this->state)
    {
    case IDLE:
        if (levelDetector.isThresholdLower()) {
            this->state = ALARM;
            //alarmLevel=true;
        }
        break;
    case ALARM:
        display.on();
        display.write("CONTAINER FULL");
        ledGreen.turnOff();
        ledRed.turnOn();
        if (door.isOpened()) {
            door.close();
            door.update();
        }
        this->state = RESET;
        //alarmLevelReset=true;
        //alarmLevel=false;
        //emptyBin=true;
        break;
    case RESET:
        ledGreen.turnOn();
        ledRed.turnOff();
        display.clear();
        this->state = IDLE;
        //alarmLevelReset=false;
        //alarmLevel=false;
        //emptyBin=false;
        break;
    default:
        break;
    }
}

void AlarmLevelTask::reset() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    this->state = IDLE;
    //alarmLevelReset=false;
    //alarmLevel=false;
    //emptyBin=false;
}