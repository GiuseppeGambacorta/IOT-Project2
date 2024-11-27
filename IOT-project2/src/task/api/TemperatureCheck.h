#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"
#include "../../Components/TemperatureSensor/api/TemperatureSensor.h"

class TemperatureCheck : public Task {
  TemperatureSensor& tempSensor;
  enum {OK, EMERGENCY} state;
  Timer* timer;

  public:

    TemperatureCheck(TemperatureSensor& sensor);
    void tick();
    void reset();
    int getState();
};

#endif