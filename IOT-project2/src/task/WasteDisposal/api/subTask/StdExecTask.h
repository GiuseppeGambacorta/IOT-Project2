#ifndef __STDEXECTASK__
#define __STDEXECTASK__

#include "../../../Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"

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
        Display display;
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
                    Display& display,
                    DigitalInput& openButton,
                    DigitalInput& closeButton,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
        void tick() override;
        void reset() override;
};

#endif 