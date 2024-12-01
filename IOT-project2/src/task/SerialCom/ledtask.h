#pragma once

#include <../Services/Services.h>
#include "./task/Task.h"
#include <ArduinoStandardLibrary.h>


class LedTask : public Task {

private:
    
  DigitalOutput& ledGreen;
  DigitalOutput& ledRed;

  Timer timerOn;
  Timer timerOff;

  int state = 0;    
public:
    LedTask(DigitalOutput& ledGreen, DigitalOutput& ledRed) 
      : ledGreen(ledGreen), ledRed(ledRed), timerOn(2000), timerOff(2000) {        
    }

    void tick() override {

        timerOn.active(state==0);
        timerOff.active(state==1);

        switch (state)
        {
        case 0:
            ledGreen.turnOn();
            ledRed.turnOff();

            if (timerOn.isTimeElapsed()) {
                state = 1;
                timerOn.reset();
            }
            break;

        case 1:
            ledGreen.turnOff();
            ledRed.turnOn();

            if (timerOff.isTimeElapsed()) {
                state = 0;
                timerOff.reset();
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
