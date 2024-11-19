#include <Arduino.h>
#include "ArduinoStandardLibrary.h"


TimeKeeper& timeKeeper = TimeKeeper::getInstance();
DigitalInput button(2,500);
DigitalOutput led(LED_BUILTIN);

AnalogInput potentiometer(A0, 100, 20);

int count = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {

  timeKeeper.update();
  button.update();
  unsigned long start = millis();
  Serial.println(start);
  potentiometer.update();
  Serial.println(millis() - start);


  if (button.isChanged() && button.isActive()){
    led.turnOn();
  }

  if (button.isChanged() && !button.isActive()){
    led.turnOff();
  }

  //Serial.println(potentiometer.getValue());

  led.update();
  timeKeeper.reset();

}

