#pragma once

#include "../../../Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>


class HomingTask : public Task {
    
    private:

        Door door;
        LiquidCrystal_I2C display;
        DigitalInput openButton;
        DigitalInput closeButton;
        DigitalOutput ledGreen;
        DigitalOutput ledRed;

    public:
        HomingTask(Door& door,
                    LiquidCrystal_I2C& display,
                    DigitalInput& openButton,
                    DigitalInput& closeButton,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
        void tick() override;
        void reset() override;
};

