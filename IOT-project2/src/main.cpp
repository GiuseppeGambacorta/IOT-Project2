/* 
Gruppo composto da :
- Giuseppe Gambacorta
- Enrico Cornacchia
- Filippo Massari 0001071420
*/

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

#include "task/WasteDisposal/api/subTask/InputTask.h"
#include "task/WasteDisposal/api/WasteDisposalTask.h"
#include "task/WasteDisposal/api/subTask/StdExecTask.h"
#include "task/WasteDisposal/api/subTask/AlarmLevelTask.h"
#include "task/WasteDisposal/api/subTask/AlarmTempTask.h"
#include "task/WasteDisposal/api/subTask/OutputTask.h"

Pir userDetector = Pir(8);
Sonar levelDetector = Sonar(13, 12);
TemperatureSensor tempSensor = TemperatureSensor(A2);
DigitalInput openButton = DigitalInput(2, 250);
DigitalInput closeButton = DigitalInput(3, 250);

Door door = Door(9);
Display display = Display(0x27, 16, 2);
DigitalOutput ledGreen(4);
DigitalOutput ledRed(5);

SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();

SerialInputTask serialinputTask;
SerialOutputTask serialoutputTask;

InputTask inputTask(levelDetector, userDetector, tempSensor, openButton, closeButton);
StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed, userDetector);
AlarmLevelTask alarmLevelTask(door, display, ledGreen, ledRed, levelDetector);
AlarmTempTask alarmTempTask(ledGreen,ledRed,display,door,tempSensor);
WasteDisposalTask wasteDisposalTask(stdExecTask, alarmLevelTask, alarmTempTask, levelDetector, tempSensor);
OutputTask outputTask(door, display ,ledGreen, ledRed);

Scheduler scheduler;


void setup() {
    serialManager.init();

    
    door.init();
    display.init();
    userDetector.calibrate();
    display.init();
    serialManager.addDebugMessage("System started");
    serialManager.addDebugMessage("System ready");
    
    scheduler.init(50);
    
    serialoutputTask.init(250);
    serialinputTask.init(500);

    inputTask.init(50);
    wasteDisposalTask.init(100);
    alarmLevelTask.init(100);
    alarmTempTask.init(100);
    stdExecTask.init(100);
    outputTask.init(100);

    serialoutputTask.setActive(true);
    serialinputTask.setActive(true);

    inputTask.setActive(true);
    wasteDisposalTask.setActive(true);
    alarmLevelTask.setActive(true);
    alarmTempTask.setActive(true);
    stdExecTask.setActive(true);
    outputTask.setActive(true);
   

    scheduler.addTask(&serialoutputTask);
    scheduler.addTask(&serialinputTask);

   
    scheduler.addTask(&inputTask);
    scheduler.addTask(&wasteDisposalTask);
    scheduler.addTask(&alarmLevelTask); 
    scheduler.addTask(&alarmTempTask);
    scheduler.addTask(&stdExecTask);
    scheduler.addTask(&outputTask);
}

void loop() {
  scheduler.schedule();
  
}