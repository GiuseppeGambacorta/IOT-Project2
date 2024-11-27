#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmTempTask.h"
#include "Components/Display/Api/Display.h"

AlarmTempTask::AlarmTempTask(DigitalOutput& ledGreen,
                               DigitalOutput& ledRed,
                               Display& display,
                               Door& door) 
                               : ledGreen(ledGreen), ledRed(ledRed), display(display), door(door) {
}

void AlarmTempTask::tick() {
    display.on();
    display.write("PROBLEM DETECTED");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
        door.update();
    }
}

void AlarmTempTask::reset() {
    // should be done outside this task
    /*ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();*/
}