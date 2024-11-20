#ifndef __TEMPERATURECHECK__
#define __TEMPERATURECHECK__

#include "Task.h"

class TemperatureCheck : public Task {

    int pin;
    int temperature;
    int threshold;

  public:

    TemperatureCheck(int pin, int threshold);
    void tick();
    void reset();
};

#endif