#include "../api/TemperatureSensor.h"
#include <Arduino.h>

#define MAXTEMP 100

TemperatureSensor::TemperatureSensor(int pin) {
    this->temperature = 0;
    this->sensor = new AnalogInput(pin, 1023);
}

void TemperatureSensor::update() {
    sensor->update();
    int analogValue = sensor->getValue();
    // Convert the analog value to a temperature value for the LM35 sensor
    this->temperature = analogValue * (5.0 / 1023.0) * 100;
}

int TemperatureSensor::readTemperature() {
    return this->temperature;
}

bool TemperatureSensor::isThresholdExceeded() {
    return this->temperature > MAXTEMP;
}