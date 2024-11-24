#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "SerialManager.h"
//#include "scheduler/api/Scheduler.h"






//Scheduler scheduler;
int i = 530;

String s = "gambacorta";
int i2 = 65;
bool start = false;
SerialManager serialManager(9600);

void setup() {
   serialManager.init();
  serialManager.addVariableToSend((byte*)&i, Type::INT);
  serialManager.addVariableToSend((byte*)&i2, Type::INT);
  serialManager.addVariableToSend(&s);
   //Serial.begin(9600);
}

void loop() {
    while (!serialManager.isSerialAvailable()) {
        Serial.println("Waiting for serial connection...");
        delay(1000);
    }

    if (!start) {
        start = Serial.read();
    }
    //scheduler.schedule();


   //Serial.println(s.length());
   // Serial.println(s.c_str());
    if (start) {
        serialManager.sendData();
        s = "gambacorta " + String(i);
        delay(1000);
    }

    

    i+=5;



}