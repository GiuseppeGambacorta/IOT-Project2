#ifndef __STDEXECTASK__
#define __STDEXECTASK__

#include "task/api/Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

enum StdExecState{
    READY,
    OPENING,
    OPEN,
    CLOSING
};

class StdExecTask : public Task {
    
private:
    StdExecState state;

    Door door;
    LiquidCrystal_I2C display;
    DigitalInput openButton;
    DigitalInput closeButton;
    DigitalOutput ledGreen;
    DigitalOutput ledRed;

public:
    StdExecTask(Door door,
                LiquidCrystal_I2C display,
                DigitalInput openButton,
                DigitalInput closeButton,
                DigitalOutput ledGreen,
                DigitalOutput ledRed);
    void tick();
    void reset();
};

#endif 