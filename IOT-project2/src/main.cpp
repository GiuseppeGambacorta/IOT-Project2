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
bool toggle = false;


void setup() {
   serialManager.init();
  serialManager.addVariableToSend((byte*)&i, VarType::INT);
  serialManager.addVariableToSend((byte*)&i2, VarType::INT);
  serialManager.addVariableToSend(&s);
  pinMode(2, OUTPUT);
   //Serial.begin(9600);
   digitalWrite(2, HIGH);
}

void loop() {
    while (!serialManager.isSerialAvailable()) {
        Serial.println("Waiting for serial connection...");
        delay(1000);
    }

    
    //scheduler.schedule();

    serialManager.doHandshake();
   //Serial.println(s.length());
   // Serial.println(s.c_str());
        serialManager.addDebugMessage("prova debug seriale");
        serialManager.addDebugMessage("prova debug seriale");
        serialManager.addEventMessage("prova evento seriale");
        toggle = !toggle;
        if (toggle){
            serialManager.addDebugMessage("prova debug seriale che capita ogni tanto");
        }
  
        serialManager.sendData();
        s = "gambacorta " + String(i);
        delay(1000);
        
    

      digitalWrite(2, !start);

    

    i+=5;



}