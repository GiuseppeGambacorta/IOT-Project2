#pragma once

#include <../Services/Services.h>
#include "./task/Task.h"
#include <ArduinoStandardLibrary.h>
#include "Components/Sonar/Api/Sonar.h"


class LedTask : public Task {

private:
    
Sonar& levelDetector;
TemperatureSensor& tempSensor;
  DigitalOutput& ledGreen;
  DigitalOutput& ledRed;


  Timer timerOn;
  Timer timerOff;

  int state = 0;   
  float level = 0; 
  int temp = 0;
  SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();
public:
    LedTask(Sonar& sonar, TemperatureSensor& tempSensor,DigitalOutput& ledGreen, DigitalOutput& ledRed) 
      : levelDetector(sonar) , tempSensor(tempSensor),ledGreen(ledGreen), ledRed(ledRed), timerOn(2000), timerOff(2000) {        
        serialManager.addVariableToSend((byte*)&temp, VarType::INT);
        serialManager.addVariableToSend((byte*)&level, VarType::FLOAT);
    }

    void tick() override {

        level = levelDetector.readDistance();
        temp = tempSensor.readTemperature();

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


        int* restore = serialManager.getvar(0);
        if (*restore == 1) {
            ledGreen.turnOn();
            ledRed.turnOn();
        }

      

       
    }
    void reset() override {
        ;
    }
};
