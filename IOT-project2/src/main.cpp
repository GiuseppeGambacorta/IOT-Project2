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

      while (!start) {
        if (Serial.available() > 0) {
            byte received =(short unsigned int) Serial.read(); // Leggo il byte come valore grezzo
            if (received == 255) {          // Controllo se è il byte 0x01
                Serial.write(10);          // Invio il byte 0x0A (10 in decimale)
                start = true;
            }
        }
    }
    //scheduler.schedule();


   //Serial.println(s.length());
   // Serial.println(s.c_str());
    if (start) {
        serialManager.addDebugMessage("prova debug seriale");
        toggle = !toggle;
        if (toggle){
            serialManager.addDebugMessage("prova debug seriale che capita ogni tanto");
        }
  
        serialManager.sendData();
        s = "gambacorta " + String(i);
        delay(1000);
        
    }

      digitalWrite(2, !start);

    

    i+=5;



}