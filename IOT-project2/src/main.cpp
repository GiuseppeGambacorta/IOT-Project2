#include <Arduino.h>
#include "ArduinoStandardLibrary.h"


ITimeKeeper& timeKeeper = MockTimeKeeper::getInstance();
DigitalInput button(2,500);
DigitalOutput led(LED_BUILTIN);

AnalogInput potentiometer(A0, 100);


AnalogOutput out (9, 100);
AnalogInput tryAnalogOut(A5, 1023);

int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  MockTimeKeeper::setTime(1000);
  timeKeeper.update();
  button.update();

  tryAnalogOut.update();
  potentiometer.update();



  if (button.isChanged() && button.isActive()){
    led.turnOn();
  }

  if (button.isChanged() && !button.isActive()){
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

