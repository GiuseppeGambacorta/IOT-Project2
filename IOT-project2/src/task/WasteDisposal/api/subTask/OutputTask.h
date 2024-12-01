#ifndef __OUTPUTTASK__
#define __OUTPUTTASK__

#include "../../../Task.h"

#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"
#include "ArduinoStandardLibrary.h"

class OutputTask : public Task {
private:
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;

public:
    OutputTask( 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed);
    void tick() override;
    void reset() override;
};

#endif