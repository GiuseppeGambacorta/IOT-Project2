#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"
#include "TemperatureSensor.h"

class TemperatureCheckTask : public Task {

    int pin;
    TemperatureSensor *sensor;
    enum {OK, HIGH_TEMP} state;

  public:

    TemperatureCheckTask(int pin, int threshold);
    void tick();
    void reset();
};

#endif