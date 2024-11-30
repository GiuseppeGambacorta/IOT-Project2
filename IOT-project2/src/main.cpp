#include <Arduino.h>

#include "scheduler/api/Scheduler.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"

#include "task/WasteDisposal/api/subTask/InputTask.h"
#include "task/WasteDisposal/api/WasteDisposalTask.h"
#include "task/WasteDisposal/api/subTask/StdExecTask.h"
#include "task/WasteDisposal/api/subTask/AlarmLevelTask.h"
#include "task/WasteDisposal/api/subTask/AlarmTempTask.h"
#include "task/WasteDisposal/api/subTask/OutputTask.h"

//#define SECURITY_MARGIN (maxTime/10)

// Componenti I/O
Pir userDetector = Pir(8);
Sonar levelDetector = Sonar(13, 12);
Door door = Door(9);
Display display = Display(0x27, 16, 2);
DigitalInput openButton = DigitalInput(2, 500);
DigitalInput closeButton = DigitalInput(5, 500);
DigitalOutput ledGreen = DigitalOutput(9);
DigitalOutput ledRed = DigitalOutput(7);
TemperatureSensor tempSensor = TemperatureSensor(2);

InputTask inputTask(userDetector, levelDetector, tempSensor, openButton, closeButton);
StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed,userDetector);
AlarmLevelTask alarmLevelTask(door,display,ledGreen,ledRed, levelDetector);
AlarmTempTask alarmTempTask(ledGreen, ledRed, display, door, tempSensor);
OutputTask outputTask(door, display, ledGreen, ledRed);

WasteDisposalTask wasteDisposalTask (stdExecTask, alarmLevelTask, alarmTempTask, levelDetector, tempSensor);

// Scheduler
Scheduler scheduler;


/*void setup() {
  Serial.begin(9600);

  //init task
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

}

void loop() {
  scheduler.schedule();
}*/

void setup() {
  Serial.begin(115200);

  //init obj
  /*Serial.println("init obj");
  userDetector.calibrate();
  Serial.println("end init obj");*/

  // init scheduler
  scheduler.init(100);

  //init task
  inputTask.init(50);
  wasteDisposalTask.init(50);

  //inserimento tank in list
  scheduler.addTask(&inputTask);
  scheduler.addTask(&wasteDisposalTask);

}

void loop() {
  scheduler.schedule();
}