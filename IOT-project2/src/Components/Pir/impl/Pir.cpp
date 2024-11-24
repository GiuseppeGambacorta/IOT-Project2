#include <Arduino.h>
#include "../api/Pir.h"

#define CALIBRATION_TIME 10

Pir::Pir(int pin) : calibrated(false), pin(pin) {
    pir = new DigitalInput(pin, 0);
}

void Pir::calibrate() {
    for (unsigned long i = 0; i < CALIBRATION_TIME; i++) {
        delay(1000);
    }
    this->calibrated = true;
    this->detected = false;
    delay(50);
}

bool Pir::isDetected() {
    if (!this->calibrated) {
        calibrate();
    }
    int current = digitalRead(this->pin);
    if (current != detected) {
        detected = current;
    }
    return detected;
}