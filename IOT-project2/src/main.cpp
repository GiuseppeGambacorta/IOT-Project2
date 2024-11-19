#include <Arduino.h>
#include "ArduinoStandardLibrary.h"


DigitalInput button(2,500);


void setup() {
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0){
    
  }
  button.update();

  


  if(button.isChanged()){
    Serial.println("Button is changed");
    Serial.println(millis());
  }
}

