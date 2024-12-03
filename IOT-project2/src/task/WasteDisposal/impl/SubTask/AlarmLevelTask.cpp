#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmLevelTask.h"
#include "Components/Display/Api/Display.h"

#define T3 3000

AlarmLevelTask::AlarmLevelTask(Door& door,
                               Display& display,
                               DigitalOutput& ledGreen,
                               DigitalOutput& ledRed,
                               Sonar& levelDetector)
                               : door(door),
                                 display(display),
                                 ledGreen(ledGreen),
                                 ledRed(ledRed),
                                 levelDetector(levelDetector),
                                 timer(T3) {
    this->state = IDLE;
    empty = ServiceLocator::getSerialManagerInstance().getvar(1);

}


void AlarmLevelTask::tick() {
    this->timer.active(this->state == EMPTY);
    switch (this->state) {
    case IDLE:
        handleIdleState();
        break;
    case ALARM:
        handleAlarmState();
        break;
    case EMPTY:
        handleEmptyState();
        break;
    case RESET:
        handleResetState();
        break;
    default:
        break;
    }
}

void AlarmLevelTask::handleIdleState() {
    if (levelDetector.isThresholdLower()) {
        this->state = ALARM;
        //alarmLevel=true;
    }
}

void AlarmLevelTask::handleAlarmState() {
    display.on();
    display.write("CONTAINER FULL");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
    }
    if (*empty == 1) {
        this->state = EMPTY;
    }
}

void AlarmLevelTask::handleEmptyState() {
    door.empty();
    if (door.isInEmptyPosition()) {
        if (timer.isTimeElapsed()) {
            this->state = RESET;
            //alarmLevelReset=true;
            //alarmLevel=false;
            //emptyBin=false;
        }
    }
}

void AlarmLevelTask::handleResetState() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    *empty = 2;
    this->state = IDLE;
    //alarmLevelReset=false;
    //alarmLevel=false;
    //emptyBin=false;
}

void AlarmLevelTask::reset() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    *empty = 0;
    this->state = IDLE;
    //alarmLevelReset=false;
    //alarmLevel=false;
    //emptyBin=false;
}

/*#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmLevelTask.h"
#include "Components/Display/Api/Display.h"

#define T3 3000

AlarmLevelTask::AlarmLevelTask(Door& door,
                               Display& display,
                               DigitalOutput& ledGreen,
                               DigitalOutput& ledRed,
                               Sonar& levelDetector)
                               : door(door),
                                 display(display),
                                 ledGreen(ledGreen),
                                 ledRed(ledRed),
                                 levelDetector(levelDetector),
                                 timer(T3) {
    this->state = IDLE;
}


void AlarmLevelTask::tick() {

    int *empty = ServiceLocator::getSerialManagerInstance().getvar(1);

    if (*empty == 1) {
        *empty = 0;
        this->state = EMPTY;
    }

    this->timer.active(this->state == EMPTY);
    switch (this->state) {/*
    case IDLE:
        handleIdleState();
        break;
    case ALARM:
        handleAlarmState();
        break;/*
    case EMPTY:
        handleEmptyState();
        break;
    case RESET:
        handleResetState();
        break;
    default:
        break;
    }
}
/*
void AlarmLevelTask::handleIdleState() {
    if (levelDetector.isThresholdLower()) {
        this->state = ALARM;
    }
}

void AlarmLevelTask::handleAlarmState() {
    display.on();
    display.write("CONTAINER FULL");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
    }
    this->state = EMPTY;
}
/*
void AlarmLevelTask::handleEmptyState() {
    door.empty();
    if (door.isInEmptyPosition()) {
        if (timer.isTimeElapsed()) {
            this->state = RESET;
        }
    }
}

void AlarmLevelTask::handleResetState() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    this->state = ALARM;
}

void AlarmLevelTask::reset() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    this->state = IDLE;
}*/