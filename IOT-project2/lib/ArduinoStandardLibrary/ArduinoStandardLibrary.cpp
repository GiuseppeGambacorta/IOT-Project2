#include "ArduinoStandardLibrary.h"


#pragma region TimeKeeper


TimeKeeper::TimeKeeper() : currentTime(0), updated(false) {}

void TimeKeeper::update() {
    if (!updated) {
        currentTime = millis();
        updated = true;
    }
}

unsigned long TimeKeeper::getCurrentTime() {
    return currentTime;
}

void TimeKeeper::reset() {
    updated = false;
}

#pragma endregion

#pragma region Timer
Timer::Timer(unsigned long timeDuration)
    : oldTime(0), timeDuration(timeDuration), startInterlock(0), timeKeeper(TimeKeeper::getInstance())
{
}

void Timer::active(bool start)
{
    if (!start){
        startInterlock = false;
    }

    if (!this->startInterlock){
        if (start){
            startInterlock = true;
            oldTime = timeKeeper.getCurrentTime();
        }
    }
}

bool Timer::isTimeElapsed()
{
    if (this->startInterlock)
    {
        unsigned long currentTime = timeKeeper.getCurrentTime();
        
        if (currentTime - this->oldTime >= this->timeDuration)
        {
            
            return true;
        }
    }
    return false;
}

void Timer::setTime(unsigned long newTime){
    this->timeDuration = newTime;
}

void Timer::reset()
{
    this->oldTime = 0;
    this->startInterlock = 0;
}
#pragma endregion


#pragma region DigitalInput
DigitalInput::DigitalInput(unsigned int pin, unsigned long threshold)
    : pin(pin), value(0), oldValue(0), trigChanged(0)
{
    pinMode(pin, INPUT);
    this->activationTimer = new Timer(threshold);
};

void DigitalInput::update()
{
    this->activationTimer->active(digitalRead(this->pin));
    this->value = this->activationTimer->isTimeElapsed();
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









