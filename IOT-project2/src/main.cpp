#include <Arduino.h>

#include "scheduler/api/Scheduler.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

#include "task/api/Task.h"
#include "task/api/ManagerTask.h"
#include "task/api/StdExecTask.h"

// Componenti I/O
Pir userDetector = Pir(9);
Sonar levelDetector = Sonar(13, 12);
Door door = Door(9);
LiquidCrystal_I2C display = LiquidCrystal_I2C(0x27, 16, 2);
DigitalInput openButton = DigitalInput(2, 500);
DigitalInput closeButton = DigitalInput(3, 500);
DigitalOutput ledGreen = DigitalOutput(5);
DigitalOutput ledRed = DigitalOutput(4);
TemperatureSensor tempSensor = TemperatureSensor(2);

// Scheduler
Scheduler scheduler;

// Tasks
ManagerTask managerTask(levelDetector, tempSensor, userDetector, scheduler.getTaskList());
StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed);

void setup() {
  Serial.begin(9600);

  // conto del tempo ottimale per i task
  
  scheduler.init(10); //inserire tempo ricavato opportunamente

  //inserimento tank in list
  scheduler.addTask(&managerTask);
  scheduler.addTask(&stdExecTask);

}

void loop() {
  scheduler.schedule();
}

