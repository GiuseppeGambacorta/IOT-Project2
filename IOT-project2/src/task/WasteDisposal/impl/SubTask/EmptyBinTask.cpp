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
     timer.active(this->entry == Entry::WAITING);
    switch (this->entry) 
    {
    case Entry::FIRST:
        door.empty();
        if (door.isInEmptyPosition()){
            this->entry = WAITING;
        }
        break;
    case Entry::WAITING:
        if (timer.isTimeElapsed()){
            ledGreen.turnOn();
            ledRed.turnOff();
            display.clear();
            this->active = false;
        }
        break;
    default:
        break;
    }

}

void EmptyBinTask::reset(){
    timer.reset();
    this->active = false;
    this->entry = FIRST;
}