#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"
#include "TemperatureSensor.h"

class TemperatureCheckTask : public Task {

  enum {OK, HIGH_TEMP} state;

  public:

    TemperatureCheckTask();
    void tick(TemperatureSensor& tempSensor);
    void reset();
};

#endif