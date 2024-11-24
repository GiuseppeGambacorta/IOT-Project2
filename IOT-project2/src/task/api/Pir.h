#ifndef __PIR__
#define __PIR__

#include "ArduinoStandardLibrary.h"
#include <Arduino.h>

class Pir{
    public:
        Pir(int pin);
        void calibrate();
        bool isDetected();
    private:
        DigitalInput* pir;
        bool calibrated;
        bool detected;
        int pin;
};

#endif