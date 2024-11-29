#ifndef __STDEXECTASK__
#define __STDEXECTASK__

#include "../../../Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"
#include "Components/Pir/Api/Pir.h"


#define OPEN_WAITING_TIME 5000
#define TSleep 10000

enum StdExecState{
    READY,
    OPEN,
    SLEEP
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

        Pir userDetector;

        bool userStatus;
        Timer userTimer = Timer(TSleep);

        void homingReady();
        void homingOpen();
        void homingSleep();

        void execReady();
        void execOpen();
        void execSleep();

    public:
        StdExecTask(Door& door,
                    Display& display,
                    DigitalInput& openButton,
                    DigitalInput& closeButton,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed,
                    Pir userDetector);
        void tick() override;
        void reset() override;
};

#endif