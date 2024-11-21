#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"
#include "TemperatureSensor.h"

class TemperatureCheck : public Task {

    int pin;
    TemperatureSensor *sensor;
    enum {OK, HIGH_TEMP} state;

  public:

    TemperatureCheck(int pin, int threshold);
    void tick();
    void reset();
};

#endif