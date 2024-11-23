#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"
#include "TemperatureSensor.h"

class TemperatureCheckTask : public Task {
  TemperatureSensor& tempSensor;
  enum {OK, HIGH_TEMP, EMERGENCY} state;
  unsigned long highTempStartTime;

  public:

    TemperatureCheckTask(TemperatureSensor& sensor);
    void tick();
    void reset();
    int getState();
};

#endif