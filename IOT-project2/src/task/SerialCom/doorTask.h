#pragma once

#include <../Services/Services.h>
#include "./task/Task.h"
#include <ArduinoStandardLibrary.h>
#include "Components/Door/Api/Door.h"


class DoorTask : public Task {

private:
    Door& door;
    Timer timerEmpty;
    Timer timerOpen;
    Timer timerClose;
    int state = 0;
    SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();

public:
    DoorTask(Door& door) 
      : door(door), timerEmpty(2000), timerOpen(2000), timerClose(2000) {        
      
    }

    void tick() override {

        timerClose.active(state==0);
        timerOpen.active(state==1);
        timerEmpty.active(state==2);
        

        switch (state)
        {
        case 0:
            door.close();

            if (timerClose.isTimeElapsed() && door.isClosed()) {
                serialManager.addEventMessage("door closed");
                state = 1;
                timerClose.reset();
            }
        
            break;

        case 1:

            door.open();
            if (timerOpen.isTimeElapsed() && door.isOpened()) {
                serialManager.addEventMessage("door opened");
                state = 2;
                timerOpen.reset();
            }
            
            break;
        case 2:
            door.empty();
            if (timerEmpty.isTimeElapsed() && door.isInEmptyPosition()) {
                serialManager.addEventMessage("door empty");
                state = 0;
                timerEmpty.reset();
            }
            break;
        default:
            break;
        }

       
    }
    void reset() override {
        ;
    }
};
