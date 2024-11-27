#include <Arduino.h>

#include "scheduler/api/Scheduler.h"

#include "ArduinoStandardLibrary.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include "Components/Display/Api/Display.h"

#include "task/WasteDisposal/api/WasteDisposalTask.h"

#define SECURITY_MARGIN (maxTime/10)

// Componenti I/O
Pir userDetector = Pir(8);
Sonar levelDetector = Sonar(13, 12);
Door door = Door(9);
Display display = Display(0x27, 16, 2);
DigitalInput openButton = DigitalInput(2, 500);
DigitalInput closeButton = DigitalInput(3, 500);
DigitalOutput ledGreen = DigitalOutput(5);
DigitalOutput ledRed = DigitalOutput(4);
TemperatureSensor tempSensor = TemperatureSensor(2);

// Scheduler
Scheduler scheduler;

WasteDisposalTask wasteDisposalTask = WasteDisposalTask(levelDetector, tempSensor, userDetector, openButton, closeButton, door, display, ledGreen, ledRed);


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

  scheduler.addTask(&wasteDisposalTask);


  
  scheduler.init(calculateOptimalPeriod(scheduler));

  for (int i = 0; i < scheduler.getNumTask(); i++) {
    Task* task = scheduler.getTask(i);
    task->reset();
  }

}

void loop() {
  scheduler.schedule();
}

