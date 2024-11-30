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

#include "task/WasteDisposal/api/subTask/InputTask.h"
#include "task/WasteDisposal/api/WasteDisposalTask.h"
#include "task/WasteDisposal/api/subTask/StdExecTask.h"
#include "task/WasteDisposal/api/subTask/AlarmLevelTask.h"
#include "task/WasteDisposal/api/subTask/AlarmTempTask.h"
#include "task/WasteDisposal/api/subTask/OutputTask.h"

//#define SECURITY_MARGIN (maxTime/10)

// Componenti I/O
/*
Pir userDetector = Pir(8);
Sonar levelDetector = Sonar(13, 12);
Door door = Door(9);
Display display = Display(0x27, 16, 2);
DigitalInput openButton = DigitalInput(2, 500);
DigitalInput closeButton = DigitalInput(3, 500);
DigitalOutput ledGreen = DigitalOutput(5);
DigitalOutput ledRed = DigitalOutput(4);
TemperatureSensor tempSensor = TemperatureSensor(2);

InputTask inputTask(userDetector, levelDetector, tempSensor, openButton, closeButton);
StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed,userDetector);
AlarmLevelTask alarmLevelTask(door,display,ledGreen,ledRed, levelDetector);
AlarmTempTask alarmTempTask(ledGreen, ledRed, display, door, tempSensor);
OutputTask outputTask(door, display, ledGreen, ledRed);

WasteDisposalTask wasteDisposalTask (stdExecTask, alarmLevelTask, alarmTempTask, levelDetector, tempSensor);
*/
// Scheduler


/*unsigned long calculateOptimalPeriod(Scheduler& scheduler) {
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
}*/


SerialInputTask serialinputTask;
SerialOutputTask serialoutputTask;
ProvaTask provaTask;
SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();
Scheduler scheduler;


void setup() {


  //init task
  /*
  inputTask.init(20);
  wasteDisposalTask.init(20);
  stdExecTask.init(20);
  alarmLevelTask.init(20);
  alarmTempTask.init(20);
  outputTask.init(20);

  //inserimento tank in list
  scheduler.addTask(&inputTask);
  scheduler.addTask(&wasteDisposalTask);
  scheduler.addTask(&alarmLevelTask);
  scheduler.addTask(&alarmTempTask);
  scheduler.addTask(&stdExecTask);
  scheduler.addTask(&outputTask);

  
  // init scheduler
  scheduler.init(150);
  */   
    serialManager.init();
    scheduler.init(25);
    scheduler.addTask(&serialinputTask);
    scheduler.addTask(&serialoutputTask);
    scheduler.addTask(&provaTask);
    serialoutputTask.setActive(true);
    serialinputTask.setActive(true);
    provaTask.setActive(true);
    serialinputTask.init(500);
    serialoutputTask.init(250);
    provaTask.init(50);



}

void loop() {
  scheduler.schedule();
}