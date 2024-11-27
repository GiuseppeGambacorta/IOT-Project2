#include <Arduino.h>

#include "scheduler/api/Scheduler.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

#include "task/api/Task.h"
#include "task/api/InputTask.h"
#include "task/api/ManagerTask.h"
#include "task/api/StdExecTask.h"
#include "task/api/SleepTask.h"
#include "task/api/OutputTask.h"

#define SECURITY_MARGIN (maxTime/10)

// Componenti I/O
Pir userDetector = Pir(8);
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
InputTask inputTask(userDetector, levelDetector, tempSensor, openButton, closeButton);
BidoneTask managerTask(levelDetector, tempSensor, userDetector, scheduler.getTaskList());
StdExecTask stdExecTask(door, display, openButton, closeButton, ledGreen, ledRed);
SleepTask sleepTask(userDetector, levelDetector, door, display, openButton, closeButton, ledGreen, ledRed, tempSensor);
OutputTask outputTask(door, display, ledGreen, ledRed);

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


void setup() {
  Serial.begin(9600);

  //inserimento tank in list
  scheduler.addInputTask(&inputTask);
  scheduler.addManagerTask(&managerTask);
  scheduler.addTask(&stdExecTask);
  scheduler.addTask(&sleepTask);
  scheduler.addOutputTask(&outputTask);
  
  scheduler.init(calculateOptimalPeriod(scheduler));

  for (int i = 0; i < scheduler.getNumTask(); i++) {
    Task* task = scheduler.getTask(i);
    task->reset();
  }

}

void loop() {
  scheduler.schedule();
}

