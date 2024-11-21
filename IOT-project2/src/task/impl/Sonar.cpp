#include <Arduino.h>
#include "task/api/Sonar.h"

Sonar::Sonar(int triggerPin, int echoPin) {
    trigger = new DigitalOutput(triggerPin);
    echo = new DigitalInput(echoPin, 1000);
}
/*
void Sonar::begin() {
    trigger.update();
    echo.update();
}

long Sonar::readDistance() {
    trigger.turnOn();
    delayMicroseconds(10);
    trigger.turnOff();

    echo.update();
    long duration = pulseIn(echo.pin, HIGH);
    return duration * 0.034 / 2;
}*/