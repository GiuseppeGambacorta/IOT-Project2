#include "task/api/OutputTask.h"

OutputTask::OutputTask(Door& door, 
              LiquidCrystal_I2C& dysplay, 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed)
    : door(door),
    dysplay(dysplay),
    ledGreen(ledGreen),
    ledRed(ledRed){
    this->type = OUT;
}

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

