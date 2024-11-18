#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#ifndef STANDARDLIBRARY_H
#define STANDARDLIBRARY_H

class DigitalInput
{
  private:
    unsigned int pin;
    unsigned int value;
    unsigned int oldValue;
    unsigned int trigChanged;
    Timer& activationTimer;

  public:
  DigitalInput(unsigned int pin, unsigned long threshold);
 
    
    void update();
    bool isActive();
    bool isChanged();
};


class DigitalOutput
{
  private:
    unsigned int pin;
    unsigned int value;

  public:
    DigitalOutput(unsigned int pin)
    {
      pinMode(pin, OUTPUT);
      this->pin = pin;
      this->value = 0;
    }
    
    void update();
    void turnOn();
    void turnOff();
    bool isActivated();

};


class Timer
{
  private:
    unsigned long oldTime;
    unsigned long timeDuration;
    unsigned int start;

  public:
    Timer(unsigned long timeDuration)
    {
      this->oldTime = 0;
      this->timeDuration = timeDuration;
      this->start = 0;
    }
    
    void active(bool start);
    bool isTimeElapsed();
    void reset();
};



class AnalogInput
{
  private:
    unsigned int pin;
    unsigned int value;
    unsigned int mapValue;
    unsigned int maxFilterSize;
    unsigned int filterCount;
    void filterValue(int inputValue);

  public:
    AnalogInput(unsigned int pin, unsigned int mapValue, unsigned int filterSize);
    void update();
    int getValue();
};


class AnalogOutput
{
  private:
    unsigned int pin;
    unsigned int value;
    unsigned int maxValue;

  public:
    AnalogOutput(unsigned int pin, unsigned int maxValue);
    
    
    void setValue(int value);
    int getValue();
    void update();
};


/*
class Screen
{
  private:
    LiquidCrystal_I2C lcd;
    bool lock;

  public:
    Screen(unsigned int address, unsigned int columns, unsigned int rows)
    {
      this->lcd = LiquidCrystal_I2C(address, columns, rows);
      this->lock = 0;
    }
    
    void clearScreen();
    void lock();
    void unlock();
    void print(String message, int row);
};


#endif



void clearScreen(Screen *screen){
  screen->lcd.clear();
  screen->lock = 0;
}

void print(Screen *screen, String message, int row, int lock)
{
  if (!lock)
  {
    screen->lock = false;
  }
  
  if (!screen->lock)
  {
    screen->lock = false;
    print(screen, message, row);
  }
 
  if (lock)
  {
    screen->lock = true;
  }
}

void print(Screen *screen, String message, int row)
{
  screen->lcd.setCursor(0, row);
  screen->lcd.print(message);

#ifdef DEBUG
  Serial.println(message);
  Serial.flush();
#endif
}


void updateDigitalInput(DigitalInput *digitalInput)
{
  updateDigitalInput(digitalInput, digitalRead(digitalInput->pin), millis());
}

void updateDigitalInput(DigitalInput *digitalInput, unsigned int inputValue, unsigned long currentTime)
{
  startTimer(&digitalInput->activationTimer, inputValue, currentTime);
  digitalInput->value = isTimeElapsed(&digitalInput->activationTimer, currentTime);
  if (digitalInput->value != digitalInput->oldValue)
  {
    digitalInput->isChanged = 1;
    digitalInput->oldValue = digitalInput->value;
  }
  else
  {
    digitalInput->isChanged = 0;
  }
}



void initDigitalOutput(DigitalOutput *digitalOutput, unsigned int pin)
{
  pinMode(pin, OUTPUT);
  digitalOutput->pin = pin;
  digitalOutput->value = 0;
}

void writeDigitalOutput(DigitalOutput *digitalOutput)
{
  digitalWrite(digitalOutput->pin, digitalOutput->value);
}

void initAnalogInput(AnalogInput *analogInput, unsigned int pin, unsigned int filterSize)
{
  pinMode(pin, INPUT);
  analogInput->pin = pin;
  analogInput->value = 0;
  analogInput->maxSizeFilter = filterSize;
  analogInput->filterCount = 0;
}

void filterAnalogValue(AnalogInput *input, int inputValue)
{
  if (input->filterCount < input->maxSizeFilter)
  {
    input->filterCount++;
  }
  float val_coef = 1.0 / float(input->filterCount);
  input->value += (inputValue - input->value) * val_coef;
}

void updateAnalogInput(AnalogInput *input)
{
  filterAnalogValue(input, analogRead(input->pin));
}

void initFadingLed(FadingLed *led, unsigned int pin, unsigned long timeDuration)
{
  pinMode(pin, OUTPUT);
  led->pin = pin;
  led->value = 0;
  led->decreasing = 0;
  unsigned int offset = 255 / 5;
  initTimer(&led->fadingTimer, (timeDuration / offset) / 2);
}

void fadeAnalogOutput(FadingLed *led)
{
  long time = millis();
  startTimer(&led->fadingTimer, true, time);
  if (isTimeElapsed(&led->fadingTimer, time))
  {
    if (led->value <= 0)
    {
      led->value = 0;
      led->decreasing = 0;
    }
    else if (led->value >= 255)
    {
      led->value = 255;
      led->decreasing = 1;
    }
    if (led->decreasing)
    {
      led->value -= 5;
    }
    else
    {
      led->value += 5;
    }
    startTimer(&led->fadingTimer, false, time);
  }
}

void turnOffFadingLed(FadingLed *led)
{
  led->value = 0;
}

void turnOnFadingLed(FadingLed *led)
{
  led->value = 255;
}






void initTimer(Timer *timer, unsigned long timeDuration)
{
  timer->start = 0;
  timer->oldTime = 0;
  timer->timeDuration = timeDuration;
}

void startTimer(Timer *timer, unsigned int start)
{
  startTimer(timer, start, millis());
}

void startTimer(Timer *timer, unsigned int start, unsigned long actualTime)
{
  if (start && !timer->start)
  {
    timer->oldTime = actualTime;
    timer->start = true;
  }
  else if (!start)
  {
    timer->start = false;
  }
}

int isTimeElapsed(Timer *timer, unsigned long actualTime)
{
  if (timer->start)
  {
    if (actualTime - timer->oldTime >= timer->timeDuration)
    {
      return true;
    }
  }
  return false;
}

*/