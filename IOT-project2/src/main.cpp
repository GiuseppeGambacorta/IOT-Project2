#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "SerialManager.h"
// #include "scheduler/api/Scheduler.h"

// Scheduler scheduler;
int i = 530;

String s = "gambacorta";
int i2 = 65;
bool start = false;
SerialManager serialManager(9600);
bool toggle = false;




void setup()
{
    serialManager.init();
    serialManager.addVariableToSend((byte *)&i, VarType::INT);
    serialManager.addVariableToSend((byte *)&i2, VarType::INT);
    serialManager.addVariableToSend(&s);
    pinMode(2, OUTPUT);
    // Serial.begin(9600);
    digitalWrite(2, HIGH);
}

void loop()
{

    // scheduler.schedule();
    if (serialManager.isSerialAvailable())
    {

        serialManager.doHandshake();

        serialManager.sendData();

        serialManager.getData();
    

        int* restore = serialManager.getvar(0);
        if (*restore == 1) {
            serialManager.addEventMessage("restore arrivato");
            *restore = 0;
        }

        int* empty = serialManager.getvar(1);
        if (*empty == 1) {
            serialManager.addEventMessage("svuota arrivato");
            *empty = 0;
        }

        s = "gambacorta " + String(i);
        delay(1000);
    }

    serialManager.addDebugMessage("prova debug seriale");
    serialManager.addDebugMessage("prova debug seriale");
    serialManager.addEventMessage("prova evento seriale");
    toggle = !toggle;
    if (toggle)
    {
        serialManager.addDebugMessage("prova debug seriale che capita ogni tanto");
    }

    digitalWrite(2, !start);

    i += 5;
}