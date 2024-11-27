#ifndef __EMPTYBINTASK__
#define __EMPTYBINTASK__

#include "task/api/Task.h"
#include "Components/Door/Api/Door.h"
#include "ArduinoStandardLibrary.h"
#include <LiquidCrystal_I2C.h>

class EmptyBinTask : public Task {
    
    private:
        Timer timer;
        Door door;
        LiquidCrystal_I2C display;
        DigitalOutput ledGreen;
        DigitalOutput ledRed;
        enum Entry{FIRST, WAITING} entry;

    public:
        EmptyBinTask(Door& door,
                    LiquidCrystal_I2C& display,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
        void tick() override;
        void reset() override;
};

#endif