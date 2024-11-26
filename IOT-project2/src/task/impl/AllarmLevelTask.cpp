#include "ArduinoStandardLibrary.h"
#include "task/api/AllarmLevelTask.h"

AllarmLevelTask::AllarmLevelTask(Door& door,
                                 LiquidCrystal_I2C& display,
                                 DigitalOutput& ledGreen,
                                 DigitalOutput& ledRed) 
                                 : door(door), display(display), ledGreen(ledGreen), ledRed(ledRed) {
    this->type = ALLARM_LEVEL;
}

void AllarmLevelTask::tick() {
    display.setCursor(0, 0);
    display.print("CONTAINER FULL");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
        door.update();
    }
    // a sleep could be used to turn off the system
    // until the operator presses "Empty the container" on the GUI
}

void AllarmLevelTask::reset() {
    ledGreen.turnOn();
    ledRed.turnOff();
    display.clear();
    // should it open the door in reverse here?
    door.empty();
    door.update();
}