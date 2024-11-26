#ifndef __ALLARMTEMPTASK__
#define __ALLARMTEMPTASK__

#include "Task.h"
#include "ArduinoStandardLibrary.h"
#include "Components/TemperatureSensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

class AllarmTempTask : public Task {
    AllarmTempTask(DigitalOutput ledGreen,
                          DigitalOutput ledRed,
                          LiquidCrystal_I2C display,
                          Door door);
    void tick() override;
};

#endif