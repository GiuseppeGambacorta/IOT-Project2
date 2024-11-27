#include "task/api/EmptyBinTask.h"

#define T3 3000

EmptyBinTask::EmptyBinTask(Door& door,
                           LiquidCrystal_I2C& display,
                           DigitalOutput& ledGreen,
                           DigitalOutput& ledRed)
    : timer(T3),
      door(door),
      display(display),
      ledGreen(ledGreen),
      ledRed(ledRed){
    this->active = true;
    this->entry = FIRST;
}

void EmptyBinTask::tick(){
    if(this->entry == FIRST){
        door.empty();
        door.update();
        this->entry = WAITING;
    }
    else if (timer.isTimeElapsed()){
        ledGreen.turnOn();
        ledRed.turnOff();
        display.clear();
    }
}

void EmptyBinTask::reset(){
    timer.reset();
    this->active = false;
    this->entry = FIRST;
}