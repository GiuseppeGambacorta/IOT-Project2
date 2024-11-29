#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmLevelTask.h"
#include "Components/Display/Api/Display.h"

#define T3 3000

AlarmLevelTask::AlarmLevelTask(Door& door,
                                 Display& display,
                                 DigitalOutput& ledGreen,
                                 DigitalOutput& ledRed,
                                 Sonar& levelDetector) 
                                 : timer(T3), door(door), display(display), ledGreen(ledGreen), ledRed(ledRed), levelDetector(levelDetector) {
    this->state = IDLE;
}

void AlarmLevelTask::tick() {
    this->timer.active(this->state == EMPTY);
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
        if(/*buttonPressed*/true){
            this->state = EMPTY;
            //alarmLevelReset=false;
            //alarmLevel=false;
            //emptyBin=true;
        }
        break;
    case EMPTY:
        door.empty();
        if (door.isInEmptyPosition()){
            if (timer.isTimeElapsed()){
            this->state = RESET;
            //alarmLevelReset=true;
            //alarmLevel=false;
            //emptyBin=false;
        }
        }
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