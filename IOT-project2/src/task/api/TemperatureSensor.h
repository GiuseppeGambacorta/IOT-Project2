#ifndef __TEMPERATURESENSOR__
#define __TEMPERATURESENSOR__

class TemperatureSensor{
    public:
        TemperatureSensor(int pin, int threshold);
        int readTemperature();
        bool isThresholdExceeded();
    private:
        int pin;
        int temperature;
};


#endif