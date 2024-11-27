#pragma once

#include "../../../Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"


class HomingTask : public Task {
    
    private:

        Door door;
        Display display;
        DigitalInput openButton;
        DigitalInput closeButton;
        DigitalOutput ledGreen;
        DigitalOutput ledRed;

    public:
        HomingTask(Door& door,
                    Display& display,
                    DigitalInput& openButton,
                    DigitalInput& closeButton,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
        void tick() override;
        void reset() override;
};

