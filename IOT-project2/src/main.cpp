#include <Arduino.h>
#include "ArduinoStandardLibrary.h"


ITimeKeeper& timeKeeper = ServiceFactory::getTimeKeeperInstance();
DigitalInput button(2,500);
DigitalOutput led(LED_BUILTIN);

AnalogInput potentiometer(A0, 100);


AnalogOutput out (9, 100);
AnalogInput tryAnalogOut(A5, 1023);


Timer ledTimerOn(1000);
Timer ledTimerOff(1000);

int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  timeKeeper.update();
  button.update();
  tryAnalogOut.update();
  potentiometer.update();

  ledTimerOn.active(!led.isActive());
  ledTimerOff.active(led.isActive());
  
  if (ledTimerOn.isTimeElapsed()){
    led.turnOn();
  }

  if (ledTimerOff.isTimeElapsed()){
    led.turnOff();
  }

  
  count++;
  count = count % 100;
  out.setValue(count);
  //Serial.println(tryAnalogOut.getValue());
  //Serial.println(potentiometer.getValue());
  Serial.println(led.isActive());
  out.update();
  led.update();

}

