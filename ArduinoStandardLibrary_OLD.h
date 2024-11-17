#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Timer
{
    int start;
    unsigned long timeDuration;
    unsigned long oldTime;
} Timer;

typedef struct DigitalInput
{
    int pin;
    int value;
    int oldValue;
    int isChanged;
    Timer activationTimer;
} DigitalInput;

typedef struct DigitalOutput
{
    int pin;
    int value;
} DigitalOutput;

typedef struct AnalogInput
{
    int pin;
    int value;
    int maxSizeFilter = 20;
    int filterCount;
} AnalogInput;

typedef struct FadingLed
{
    int pin;
    int value;
    int decreasing;
    Timer fadingTimer;
} FadingLed;


typedef struct Screen
{
    LiquidCrystal_I2C lcd;
    unsigned int rows;
    unsigned int columns;
    unsigned int lock;
} Screen;

#define LOCK 1
#define UNLOCK 0

void clearScreen(Screen *screen);
void print(Screen* screen, String message, int row, int lock);
void print(Screen* screen, String message, int row);


void initDigitalInput(DigitalInput *digitalInput, unsigned int pin, unsigned long threshold);
void updateDigitalInput(DigitalInput *digitalInput);
void updateDigitalInput(DigitalInput *digitalInput, unsigned int inputValue, unsigned long currentTime);

void initDigitalOutput(DigitalOutput *digitalOutput, unsigned int pin);
void writeDigitalOutput(DigitalOutput *digitalOutput);

void initAnalogInput(AnalogInput *digitalInput, unsigned int pin, unsigned int filterSize);
void filterAnalogValue(AnalogInput *input, int inputValue);
void updateAnalogInput(AnalogInput *input);

void initFadingLed(FadingLed *led, unsigned int pin, unsigned long timeDuration);
void fadeAnalogOutput(FadingLed *digitalOutput);
void turnOffFadingLed(FadingLed *led);
void turnOnFadingLed(FadingLed *led);


void initTimer(Timer *timer, unsigned long timeDuration);
void startTimer(Timer *timer, unsigned int start);
void startTimer(Timer *timer, unsigned int start, unsigned long actualTime);
int isTimeElapsed(Timer *timer, unsigned long actualTime);

#endif // !FUNC_H
