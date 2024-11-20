#include "TemperatureCheck.h"
#include "Arduino.h"

TemperatureCheck::TemperatureCheck(int pin, int threshold) {
    this->pin = pin;
    this->threshold = threshold;
}