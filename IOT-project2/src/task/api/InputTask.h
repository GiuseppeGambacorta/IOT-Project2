#ifndef __INPUTTASK__
#define __INPUTTASK__

#include "task/api/Task.h"

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
    DigitalInput& openButton;
    DigitalInput& closeButton;

public:
    InputTask(Pir& userDetector, 
              Sonar& levelDetector, 
              TemperatureSensor& tempSensor,  
              DigitalInput& openButton, 
              DigitalInput& closeButton);
    void tick() override;
    void reset() override;
};

#endif