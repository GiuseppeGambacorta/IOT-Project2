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
#include "task/SerialCom/doorTask.h"
#include "task/SerialCom/ledtask.h"
#include "task/SerialCom/buttonsTask.h"

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
Door door = Door(11);
Display display = Display(0x27, 16, 2);
DigitalInput openButton = DigitalInput(2, 500);
DigitalInput closeButton = DigitalInput(5, 500);

TemperatureSensor tempSensor = TemperatureSensor(2);

InputTask inputTask(userDetector, levelDetector, tempSensor, openButton, closeButton);

StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed, userDetector);

AlarmLevelTask alarmLevelTask(door,display,ledGreen,ledRed, levelDetector);
AlarmTempTask alarmTempTask(ledGreen, ledRed, display, door, tempSensor);
OutputTask outputTask(door, display, ledGreen, ledRed);
*/
//WasteDisposalTask wasteDisposalTask (stdExecTask, alarmLevelTask, alarmTempTask, levelDetector, tempSensor);

// Scheduler



SerialInputTask serialinputTask;
SerialOutputTask serialoutputTask;

SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();






//Pir userDetector = Pir(8);
Sonar levelDetector = Sonar(13, 12);
//TemperatureSensor tempSensor = TemperatureSensor(3);
DigitalInput openButton = DigitalInput(2, 500);
DigitalInput closeButton = DigitalInput(5, 500);



Door door = Door(11);
Display display = Display(0x27, 16, 2);
DigitalOutput ledGreen(9);
DigitalOutput ledRed(7);


InputTask inputTask(levelDetector, openButton, closeButton);

LedTask ledTask(levelDetector, ledGreen, ledRed);

DoorTask doorTask(door);

ButtonsTask buttonsTask(openButton, closeButton);

OutputTask outputTask(door, display ,ledGreen, ledRed);



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
  //scheduler.addTask(&wasteDisposalTask);
  //scheduler.addTask(&alarmLevelTask);
  //scheduler.addTask(&alarmTempTask);
  scheduler.addTask(&stdExecTask);
  scheduler.addTask(&outputTask);

  
  // init scheduler
  scheduler.init(150);
  */   


 

    serialManager.init();
    door.init();
    
    scheduler.init(25);
    serialoutputTask.init(250);
    serialinputTask.init(500);

    inputTask.init(50);
    ledTask.init(50);
    doorTask.init(50);
    buttonsTask.init(50);
    outputTask.init(50);


    serialoutputTask.setActive(true);
    serialinputTask.setActive(true);

    inputTask.setActive(true);
    ledTask.setActive(true);
    doorTask.setActive(true);
    buttonsTask.setActive(true);
    outputTask.setActive(true);
   


    scheduler.addTask(&serialoutputTask);
    scheduler.addTask(&serialinputTask);

   
    scheduler.addTask(&inputTask);
    scheduler.addTask(&ledTask);
    scheduler.addTask(&doorTask);
    scheduler.addTask(&buttonsTask);
    scheduler.addTask(&outputTask);

 
    


}

void loop() {
  //Serial.println("loop");
  scheduler.schedule();

  

}