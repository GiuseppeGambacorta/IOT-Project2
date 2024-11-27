#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/AlarmLevelTask.h"
#include "Components/Display/Api/Display.h"

AlarmLevelTask::AlarmLevelTask(Door& door,
                                 Display& display,
                                 DigitalOutput& ledGreen,
                                 DigitalOutput& ledRed) 
                                 : door(door), display(display), ledGreen(ledGreen), ledRed(ledRed) {
}

void AlarmLevelTask::tick() {
    display.on();
    display.write("CONTAINER FULL");
    ledGreen.turnOff();
    ledRed.turnOn();
    if (door.isOpened()) {
        door.close();
        door.update();
    }
}

void AlarmLevelTask::reset() {
}