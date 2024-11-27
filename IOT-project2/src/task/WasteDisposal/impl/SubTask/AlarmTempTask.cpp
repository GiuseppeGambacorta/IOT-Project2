#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmTempTask.h"

AlarmTempTask::AlarmTempTask(DigitalOutput& ledGreen,
                               DigitalOutput& ledRed,
                               LiquidCrystal_I2C& display,
                               Door& door) 
                               : ledGreen(ledGreen), ledRed(ledRed), display(display), door(door) {
}

void AlarmTempTask::tick() {
    display.setCursor(0, 0);
    display.print("PROBLEM DETECTED");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
        door.update();
    }
    // a sleep could be used to turn off the system
    // until the operator presses reset on the GUI
}

void AlarmTempTask::reset() {
    // should be done outside this task
    /*ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();*/
}