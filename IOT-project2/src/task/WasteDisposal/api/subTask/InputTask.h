#ifndef __INPUTTASK__
#define __INPUTTASK__

#include "../../../Task.h"

#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"
#include "ArduinoStandardLibrary.h"

class InputTask : public Task {
private:

    DigitalInput& openButton;
    DigitalInput& closeButton;

public:
    InputTask(
              DigitalInput& openButton, 
              DigitalInput& closeButton);
    void tick() override;
    void reset() override;
};

#endif