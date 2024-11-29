#include "ArduinoStandardLibrary.h"
#include "../../api/subTask/SleepTask.h"
#include "Components/Display/Api/Display.h"
#include "avr/sleep.h"
#include "EnableInterrupt.h"

SleepTask::SleepTask(Pir& userDetector, Sonar& levelDetector, Door& door, Display& display,
                     DigitalInput& openButton, DigitalInput& closeButton, DigitalOutput& ledGreen,
                     DigitalOutput& ledRed, TemperatureSensor& tempSensor) 
                     : userDetector(userDetector), levelDetector(levelDetector), door(door), display(display),
                       openButton(openButton), closeButton(closeButton), ledGreen(ledGreen), ledRed(ledRed),
                       tempSensor(tempSensor) {}
/*
void wakeUp() {
}*/

void SleepTask::tick() {
    display.off();/*
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    enableInterrupt(userDetector.getPin(), wakeUp, HIGH);
    sleep_mode();
    disableInterrupt(userDetector.getPin());
    sleep_disable();*/
    display.on();
}

void SleepTask::reset() {
    display.on();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}