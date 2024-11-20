#include "ArduinoStandardLibrary.h"


/*---- TIME KEEPER ----*/

TimeKeeper::TimeKeeper() : ITimeKeeper() {}

void TimeKeeper::update() {
    this->currentTime = millis();
}



/*---- MOCK TIME KEEPER ----*/
void MockTimeKeeper::update() {
    ;
}

void MockTimeKeeper::setTime(unsigned long newTime) {
    this->currentTime = newTime;
}





/*---- TIMER ----*/

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



/*---- DIGITAL INPUT ----*/

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



/*---- DIGITAL OUTPUT ----*/


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

bool DigitalOutput::isActive()
{
    return this->value;
};



/*---- ANALOG INPUT ----*/


AnalogInput::AnalogInput(unsigned int pin, unsigned int mapValue)
    : pin(pin), value(0),  mapValue(mapValue), filterCount(0)
{
    pinMode(pin, INPUT);
};


float AnalogInput::filterValue(unsigned int inputValue) {
    array[currentIndex] = inputValue; // Memorizza il valore letto nell'array
    currentIndex = (currentIndex + 1) % maxFilterSize; // Aggiorna l'indice corrente

    unsigned long sum = 0;
    for (unsigned int i = 0; i < maxFilterSize; i++) {
        sum += array[i]; // Calcola la somma dei valori nell'array
    }

    return sum / maxFilterSize; // Restituisce la media dei valori
}

void AnalogInput::update(){
      this->value += this->filterValue(map(analogRead(this->pin), 0, 1023, 0, this->mapValue));
  
}


int AnalogInput::getValue(){
    return this->value;
}



/*---- ANALOG OUTPUT ----*/


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










