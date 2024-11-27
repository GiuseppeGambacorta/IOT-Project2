#include "ArduinoStandardLibrary.h"
#include "task/api/SleepTask.h"
#include "avr/sleep.h"
#include "EnableInterrupt.h"

SleepTask::SleepTask(Pir& userDetector, Sonar& levelDetector, Door& door, LiquidCrystal_I2C& display,
                     DigitalInput& openButton, DigitalInput& closeButton, DigitalOutput& ledGreen,
                     DigitalOutput& ledRed, TemperatureSensor& tempSensor) 
                     : userDetector(userDetector), levelDetector(levelDetector), door(door), display(display),
                       openButton(openButton), closeButton(closeButton), ledGreen(ledGreen), ledRed(ledRed),
                       tempSensor(tempSensor) {}

void wakeUp() {
}

void SleepTask::tick() {
    display.noDisplay();
    display.noBacklight();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    enableInterrupt(userDetector.getPin(), wakeUp, HIGH);
    sleep_mode();
    disableInterrupt(userDetector.getPin());
    sleep_disable();
    display.display();
    display.backlight();
}

void SleepTask::reset() {
    display.display();
    display.backlight();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}