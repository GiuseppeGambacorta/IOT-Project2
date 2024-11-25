#ifndef __STDEXECTASK__
#define __STDEXECTASK__

#include "task/api/Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

#define OPEN_WAITING_TIME 5000

enum StdExecState{
    READY,
    OPEN
};

class StdExecTask : public Task {
    
    private:
        StdExecState state;

        Timer timer;

        Door door;
        LiquidCrystal_I2C display;
        DigitalInput openButton;
        DigitalInput closeButton;
        DigitalOutput ledGreen;
        DigitalOutput ledRed;

        void homingReady();
        void homingOpen();

        void execReady();
        void execOpen();

    public:
        StdExecTask(Door& door,
                    LiquidCrystal_I2C& display,
                    DigitalInput& openButton,
                    DigitalInput& closeButton,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
        void tick() override;
        void reset() override;
};

#endif 