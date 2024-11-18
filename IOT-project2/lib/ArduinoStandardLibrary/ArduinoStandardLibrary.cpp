#include "ArduinoStandardLibrary.h"


#pragma region DigitalInput
DigitalInput::DigitalInput(unsigned int pin, unsigned long threshold)
    : pin(pin), value(0), oldValue(0), trigChanged(0)
{
    pinMode(pin, INPUT);
    this->activationTimer = new Timer(threshold);
};

void DigitalInput::update()
{
    this->value = digitalRead(this->pin);
    this->trigChanged = this->value != this->oldValue;
    this->oldValue = this->value;

};

bool DigitalInput::isActive(){
    return this->value;
}

bool DigitalInput::isChanged(){
    return this->trigChanged;
}
#pragma endregion

#pragma region DigitalOutput
DigitalOutput::DigitalOutput(unsigned int pin)
    : pin(pin), value(0)
{
    pinMode(pin, OUTPUT);
};


void DigitalOutput::update()
{
    digitalWrite(this->pin, this->value);
};

void DigitalOutput::turnOn()
{
    this->value = 1;
};

void DigitalOutput::turnOff()
{
    this->value = 0;
};

bool DigitalOutput::isActivated()
{
    return this->value;
};
#pragma endregion

#pragma region Timer
Timer::Timer(unsigned long timeDuration)
    : oldTime(0), timeDuration(timeDuration), start(0)
{
};

void Timer::active(bool start)
{
    this->start = start;
    if (start)
    {
        this->oldTime = millis();
    }
};


bool Timer::isTimeElapsed()
{
    if (this->start)
    {
        unsigned long currentTime = millis();
        if (currentTime - this->oldTime >= this->timeDuration)
        {
            return true;
        }
    }
    return false;
};

void Timer::reset()
{
    this->oldTime = 0;
    this->start = 0;
};
#pragma endregion

#pragma region AnalogInput
AnalogInput::AnalogInput(unsigned int pin, unsigned int mapValue,unsigned int filterSize)
    : pin(pin), value(0),  mapValue(mapValue),maxFilterSize(filterSize), filterCount(0)
{
    pinMode(pin, INPUT);
};


void AnalogInput::filterValue(int inputValue){
    if(this->filterCount < this->maxFilterSize){
        this->filterCount++;
    }
    float val_coef = 1.0 / float(this->filterCount);
    this->value += (inputValue - this->value) * val_coef;
}

void AnalogInput::update(){
    this->filterValue(analogRead(this->pin));
    this->value = map(this->value, 0, 1023, 0, this->mapValue);
}


int AnalogInput::getValue(){
    return this->value;
}


#pragma endregion

#pragma region AnalogOutput

AnalogOutput::AnalogOutput(unsigned int pin, unsigned int maxValue)
    : pin(pin), value(0), maxValue(maxValue)
{
    pinMode(pin, OUTPUT);
};


void AnalogOutput::setValue(unsigned int value){
    if(value > this->maxValue){
        value = this->maxValue;
    }
}



int AnalogOutput::getValue(){
    return this->value;
}


void AnalogOutput::update(){
    analogWrite(this->pin, map(this->value, 0, this->maxValue, 0, 255));
}

#pragma endregion









