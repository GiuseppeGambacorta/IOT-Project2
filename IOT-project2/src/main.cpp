#include <Arduino.h>
#include "ArduinoStandardLibrary.h"


TimeKeeper& timeKeeper = TimeKeeper::getInstance();
DigitalInput button(2,500);
Timer timer(1000);
int count = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {

  timeKeeper.update();
  button.update();


  if (button.isChanged() && button.isActive()){
    Serial.println("premuto");
  }

  timeKeeper.reset();

}

