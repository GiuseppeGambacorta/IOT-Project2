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
//#include "task/SerialCom/provaTask.h"

#include "task/WasteDisposal/api/subTask/InputTask.h"
#include "task/WasteDisposal/api/WasteDisposalTask.h"
#include "task/WasteDisposal/api/subTask/StdExecTask.h"
#include "task/WasteDisposal/api/subTask/AlarmLevelTask.h"
#include "task/WasteDisposal/api/subTask/AlarmTempTask.h"
#include "task/WasteDisposal/api/subTask/OutputTask.h"

Pir userDetector = Pir(8);
Sonar levelDetector = Sonar(13, 12);
TemperatureSensor tempSensor = TemperatureSensor(A2);
DigitalInput openButton = DigitalInput(2, 50);
DigitalInput closeButton = DigitalInput(3, 50);

Door door = Door(9);
Display display = Display(0x27, 16, 2);
DigitalOutput ledGreen(4);
DigitalOutput ledRed(5);

//SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();

//SerialInputTask serialinputTask;
//SerialOutputTask serialoutputTask;

//AnalogInput potenziometro(A2,100);
int tempo = 0;

InputTask inputTask(levelDetector, userDetector, tempSensor, openButton, closeButton);
StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed, userDetector);
AlarmLevelTask alarmLevelTask(door, display, ledGreen, ledRed, levelDetector);
AlarmTempTask alarmTempTask(ledGreen,ledRed,display,door,tempSensor);
WasteDisposalTask wasteDisposalTask(stdExecTask, alarmLevelTask, alarmTempTask, levelDetector, tempSensor);
OutputTask outputTask(door, display ,ledGreen, ledRed);

//LedTask ledTask(levelDetector, tempSensor, ledGreen, ledRed);
//DoorTask doorTask(door, userDetector, display);
//ButtonsTask buttonsTask(openButton, closeButton);
//ProvaTask provaTask;

Scheduler scheduler;


void setup() {
  Serial.begin(9600);
    //serialManager.init();

    
    door.init();
    userDetector.calibrate();
    //display.init();
    //serialManager.addDebugMessage("System started");
    Serial.println("System started");
    
    scheduler.init(500);

    //serialoutputTask.init(250);
    //serialinputTask.init(500);

    inputTask.init(100);
    wasteDisposalTask.init(100);
    alarmLevelTask.init(100);
    alarmTempTask.init(100);
    stdExecTask.init(100);
    outputTask.init(100);

    //ledTask.init(50);
    //doorTask.init(50);
    //buttonsTask.init(50);
    //provaTask.init(50);


    //serialoutputTask.setActive(true);
    //serialinputTask.setActive(true);

    inputTask.setActive(true);
    wasteDisposalTask.setActive(true);
    alarmLevelTask.setActive(true);
    alarmTempTask.setActive(true);
    stdExecTask.setActive(true);
    outputTask.setActive(true);

    //ledTask.setActive(true);
    //doorTask.setActive(true);
    //buttonsTask.setActive(true);
    //provaTask.setActive(true);
   
    //scheduler.addTask(&serialoutputTask);
    //scheduler.addTask(&serialinputTask);

   
    scheduler.addTask(&inputTask);
    scheduler.addTask(&wasteDisposalTask);
    scheduler.addTask(&alarmLevelTask); 
    scheduler.addTask(&alarmTempTask);
    scheduler.addTask(&stdExecTask);
    scheduler.addTask(&outputTask);

    //scheduler.addTask(&provaTask);
    //scheduler.addTask(&ledTask);
    //scheduler.addTask(&doorTask);
    //scheduler.addTask(&buttonsTask);
}

void loop() {
  scheduler.schedule();
  
}