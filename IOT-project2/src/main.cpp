#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "SerialManager.h"
//#include "scheduler/api/Scheduler.h"






//Scheduler scheduler;
int i = 530;

String s = "gambacorta";
int i2 = 65;
SerialManager serialManager(9600);

void setup() {
   serialManager.init();
  serialManager.addVariableToSend((byte*)&i, Type::INT);
  serialManager.addVariableToSend((byte*)&i2, Type::INT);
  //serialManager.addVariableToSend(&s);
   //Serial.begin(9600);
}

void loop() {
    while (!serialManager.isSerialAvailable()) {
        Serial.println("Waiting for serial connection...");
        delay(1000);
    }

    //scheduler.schedule();


   //Serial.println(s.length());
   // Serial.println(s.c_str());
    serialManager.sendData();
    delay(1000);

    i+=5;

    if (i > 600) {
        s = "ciao bello";
    }

}