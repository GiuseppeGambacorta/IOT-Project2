#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "ArduinoStandardLibrary.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>

#include "task/api/Task.h"

#define MAX_TASKS 10

class Scheduler {

private: 
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  SchedulerTimer timer;

  // Componenti I/O
  Pir userDetector; // Sensore PIR
  Sonar levelDetector; // Sonar
  Door door; // Servo-motore
  LiquidCrystal_I2C display; // Display
  DigitalInput openButton; // Pulsante OPEN
  DigitalInput closeButton; // Pulsante CLOSE
  DigitalOutput ledGreen; // LED verde
  DigitalOutput ledRed; // LED rosso
  TemperatureSensor tempSensor; // Sensore di temperatura

public:
  Scheduler()
    : userDetector(9), 
      levelDetector(13, 12),
      display(0x27, 16, 2), 
      openButton(2, 500),
      closeButton(3, 500),
      ledGreen(5),
      ledRed(4),
      tempSensor(2),
      door(9)
  {}

  void init(int basePeriod);  
  bool addTask(Task* task);  
  void schedule();
};

#endif