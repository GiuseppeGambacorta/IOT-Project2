#include "task/api/OutputTask.h"

OutputTask::OutputTask(Door& door, 
              LiquidCrystal_I2C& display, 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed)
    : door(door),
    display(display),
    ledGreen(ledGreen),
    ledRed(ledRed){}

void OutputTask::tick(){
    door.update();
    //dysplay.update();
    ledGreen.update();
    ledRed.update();
}

void OutputTask::reset(){
    door.update();
    //dysplay.update();
    ledGreen.update();
    ledRed.update();
}

