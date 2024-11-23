#include <Arduino.h>
#include "task/api/Pir.h"

#define CALIBRATION_TIME 10000

Pir::Pir(int pin) : calibrated(false) {
    pir = new DigitalInput(pin, 1);
}

void Pir::calibrate() {
    Serial.print("Calibrating sensor... ");
    for (unsigned long i = 0; i < CALIBRATION_TIME / 1000; i++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" done");
    Serial.println("PIR SENSOR READY.");
    calibrated = true;
}

bool Pir::isDetected() {
    if (!calibrated) {
        calibrate();
    }
    pir->update();
    return pir->isActive();
}