#include <Arduino.h>
#include "../api/Sonar.h"

#define D1 10;
const double vs = 331.45 + 0.62*20;

Sonar::Sonar(int triggerPin, int echoPin) {
    this->echoPin = echoPin;
    trigger = new DigitalOutput(triggerPin);
    echo = new DigitalInput(echoPin, 1000);
}

void Sonar::update() {
    // Send pulse
    trigger->turnOn();
    trigger->update();
    delayMicroseconds(3);
    trigger->turnOff();
    trigger->update();
    delayMicroseconds(5);
    trigger->turnOn();
    trigger->update();
    // Read pulse
    long tUS = pulseInLong(this->echoPin, HIGH);
    double t = tUS / 1000.0 / 1000.0 / 2;
    this->level = t * vs;
}

float Sonar::readDistance() {
    return this->level;
}

bool Sonar::isThresholdLower() {
    return this->level < D1;
}