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
#include "task/SerialCom/ProvaTask.h"


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





SerialInputTask inputTask;
SerialOutputTask outputTask;
ProvaTask provaTask;
SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();
Scheduler scheduler;

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

    scheduler.init(25);
    scheduler.addTask(&inputTask);
    scheduler.addTask(&outputTask);
    scheduler.addTask(&provaTask);
    outputTask.setActive(true);
    inputTask.setActive(true);
    provaTask.setActive(true);
    inputTask.init(500);
    outputTask.init(250);
    provaTask.init(50);



    serialManager.init();

    pinMode(2, OUTPUT);
    // Serial.begin(9600);
    digitalWrite(2, HIGH);


}

void loop() {



    scheduler.schedule();
    

    
}

