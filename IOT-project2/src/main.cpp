#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "SerialManager.h"
//#include "scheduler/api/Scheduler.h"






//Scheduler scheduler;
int i = 530;
int i2 =1000;
SerialManager serialManager(9600);

void setup() {
    serialManager.init();
    serialManager.addVariableToSend((byte*)&i, Type::INT);
    
}

void loop() {
    while (!serialManager.isSerialAvailable()) {
        Serial.println("Waiting for serial connection...");
        delay(1000);
    }

    //scheduler.schedule();



    serialManager.sendData();
    delay(1000);
    DataHeader header;

    i+=5;

}