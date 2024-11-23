#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"
#include "TemperatureSensor.h"

class TemperatureCheckTask : public Task {
  TemperatureSensor& tempSensor;
  enum {OK, EMERGENCY} state;
  Timer* timer;

  public:

    TemperatureCheckTask(TemperatureSensor& sensor);
    void tick();
    void reset();
    int getState();
};

#endif