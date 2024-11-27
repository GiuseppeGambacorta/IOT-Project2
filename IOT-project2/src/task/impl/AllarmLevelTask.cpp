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
}

void AllarmLevelTask::reset() {
}