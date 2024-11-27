#ifndef __EMPTYBINTASK__
#define __EMPTYBINTASK__

#include "../../../Task.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"
#include "ArduinoStandardLibrary.h"

class EmptyBinTask : public Task {
    
    private:
        Timer timer;
        Door door;
        Display display;
        DigitalOutput ledGreen;
        DigitalOutput ledRed;
        enum Entry{FIRST, WAITING} entry;

    public:
        EmptyBinTask(Door& door,
                    Display& display,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
        void tick() override;
        void reset() override;
};

#endif