#ifndef __ALLARMLEVELTASK__
#define __ALLARMLEVELTASK__

#include "Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

class AllarmLevelTask : public Task {

private:

public:
    AllarmLevelTask(Door door,
                    LiquidCrystal_I2C display,
                    DigitalOutput ledGreen,
                    DigitalOutput ledRed);
    void tick() override;
};

#endif