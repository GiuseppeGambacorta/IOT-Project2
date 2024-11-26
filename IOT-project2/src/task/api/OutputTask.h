#ifndef __OUTPUTTASK__
#define __OUTPUTTASK__

#include "task/api/Task.h"
#include "task/TasksType.h"

#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>
#include "ArduinoStandardLibrary.h"

class OutputTask : public Task {
private:
    Door& door;
    LiquidCrystal_I2C& dysplay;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;

public:
    OutputTask(Door& door, 
              LiquidCrystal_I2C& dysplay, 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed);
    void tick() override;
    void reset() override;
};

#endif