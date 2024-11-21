#include "task/api/TemperatureSensor.h"
#include <Arduino.h>

TemperatureSensor::TemperatureSensor(int pin, int threshold) {
    this->pin = pin;
    this->threshold = threshold;
    this->temperature = 0;
    pinMode(pin, INPUT);
}

int TemperatureSensor::readTemperature() {
    // Read the analog value from the sensor
    int analogValue = analogRead(pin);
    // Convert the analog value to a temperature value for the LM35 sensor
    this->temperature = analogValue * (5.0 / 1023.0) * 100;
    return this->temperature;
}

bool TemperatureSensor::isThresholdExceeded() {
    // Check if the temperature exceeds the threshold
    return readTemperature() > this->threshold;
}