#include "task/api/TemperatureSensor.h"
#include <Arduino.h>

#define MAXTEMP 100

TemperatureSensor::TemperatureSensor(int pin) {
    this->temperature = 0;
    this->sensor = new AnalogInput(pin, 1023);
}

int TemperatureSensor::readTemperature() {
    // Read the analog value from the sensor
    sensor->update();
    int analogValue = sensor->getValue();
    // Convert the analog value to a temperature value for the LM35 sensor
    this->temperature = analogValue * (5.0 / 1023.0) * 100;
    return this->temperature;
}

bool TemperatureSensor::isThresholdExceeded() {
    // Check if the temperature exceeds the threshold
    return readTemperature() > MAXTEMP;
}