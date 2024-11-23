#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>
#include "ArduinoStandardLibrary.h"

class Sonar {
public:
    Sonar(int triggerPin, int echoPin);
    float readDistance();
    bool isThresholdLower();

private:
    int echoPin;
    double level;
    DigitalOutput* trigger;
    DigitalInput* echo;
};

#endif