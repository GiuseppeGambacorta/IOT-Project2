#include <Arduino.h>

#include "scheduler/api/Scheduler.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"
#include "task/SerialCom/SerialInput.h"
#include "task/SerialCom/SerialOutput.h"


#define SECURITY_MARGIN (maxTime/10)





unsigned long calculateOptimalPeriod(Scheduler& scheduler) {
    unsigned long maxTime = 0;

    for (int i = 0; i < scheduler.getNumTask(); i++) {
        Task* task = scheduler.getTask(i);

        if (task != nullptr) {
            unsigned long startTime = micros();
            task->tick(); 
            unsigned long elapsedTime = micros() - startTime;

            if (elapsedTime > maxTime) {
                maxTime = elapsedTime;
            }
        }
    }
    maxTime += SECURITY_MARGIN;
    return maxTime;
}


int i = 530;
String s = "gambacorta";
int i2 = 65;
bool start = false;

bool toggle = false;


SerialInputTask inputTask();
SerialOutputTask outputTask();
SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();

void setup() {

  //inserimento tank in list

  //scheduler.addTask(&inputTask);
  //scheduler.addTask(&alarmLevelTask);
  //scheduler.addTask(&alarmTempTask);

  //scheduler.addTask(&wasteDisposalTask);
  //scheduler.addTask(&emptyBinTask);
  //scheduler.addTask(&homingTask);
  //scheduler.addTask(&stdExecTask);
  //scheduler.addTask(&sleepTask);

  //scheduler.addTask(&outputTask);


    serialManager.init();
    serialManager.addVariableToSend((byte *)&i, VarType::INT);
    serialManager.addVariableToSend((byte *)&i2, VarType::INT);
    serialManager.addVariableToSend(&s);
    pinMode(2, OUTPUT);
    // Serial.begin(9600);
    digitalWrite(2, HIGH);


}

void loop() {



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

