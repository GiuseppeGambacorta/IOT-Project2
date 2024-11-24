#ifndef __INPUTTASK__
#define __INPUTTASK__

#include "task/api/Task.h"
#include "task/TasksType.h"

#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>
#include "ArduinoStandardLibrary.h"

class InputTask : public Task {
private:
    Pir& userDetector;
    Sonar& levelDetector;
    TemperatureSensor& tempSensor;
    Door& door;
    LiquidCrystal_I2C& display;
    DigitalInput& openButton;
    DigitalInput& closeButton;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;

public:
    InputTask(Pir& userDetector, 
              Sonar& levelDetector, 
              TemperatureSensor& tempSensor, 
              Door& door, 
              LiquidCrystal_I2C& display, 
              DigitalInput& openButton, 
              DigitalInput& closeButton, 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed)
        : userDetector(userDetector), 
          levelDetector(levelDetector), 
          tempSensor(tempSensor), 
          door(door), 
          display(display), 
          openButton(openButton), 
          closeButton(closeButton), 
          ledGreen(ledGreen), 
          ledRed(ledRed) {
            this->type = IN;
          }

    void tick() override {}

    void reset() override {}
};

#endif