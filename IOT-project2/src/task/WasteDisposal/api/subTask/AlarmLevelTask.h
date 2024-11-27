#ifndef __ALARMLEVELTASK__
#define __ALARMLEVELTASK__

#include "../../../Task.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"

class AlarmLevelTask : public Task {

private:
    Door& door;
    Display& display;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;
public:
    AlarmLevelTask(Door& door,
                    Display& display,
                    DigitalOutput& ledGreen,
                    DigitalOutput& ledRed);
    void tick() override;
    void reset() override;
};

#endif