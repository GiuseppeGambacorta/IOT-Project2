#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>
#include "ArduinoStandardLibrary.h"

class Sonar {
public:
    Sonar(int triggerPin, int echoPin);
    void begin();
    long readDistance();

private:
    DigitalOutput* trigger;
    DigitalInput* echo;
};

#endif