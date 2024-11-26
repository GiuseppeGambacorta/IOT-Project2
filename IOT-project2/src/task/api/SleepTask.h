#ifndef __SLEEPTASK__
#define __SLEEPTASK__

#include "Task.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

class SleepTask : public Task {
private:
    Pir& userDetector;
    Sonar& levelDetector;
    Door& door;
    LiquidCrystal_I2C& display;
    DigitalInput& openButton;
    DigitalInput& closeButton;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;
    TemperatureSensor& tempSensor;

public:
    SleepTask(Pir& userDetector, 
            Sonar& levelDetector,
            Door& door, 
            LiquidCrystal_I2C& display,
            DigitalInput& openButton, 
            DigitalInput& closeButton, 
            DigitalOutput& ledGreen,
            DigitalOutput& ledRed, 
            TemperatureSensor& tempSensor);
    void tick() override;
    void reset() override;
};

#endif