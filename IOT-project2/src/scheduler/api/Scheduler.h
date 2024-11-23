#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "ArduinoStandardLibrary.h"
#include "task/api/Task.h"
#include "task/api/ManagerTask.h"
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define MAX_TASKS 10

class Scheduler {

private: 
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  SchedulerTimer timer;

  // Componenti I/O
  DigitalInput userDetector; // Sensore PIR
  AnalogInput levelDetector; // Sonar
  Servo door; // Servo-motore
  LiquidCrystal_I2C display; // Display
  DigitalInput openButton; // Pulsante OPEN
  DigitalInput closeButton; // Pulsante CLOSE
  DigitalOutput ledGreen; // LED verde
  DigitalOutput ledRed; // LED rosso
  AnalogInput tempSensor; // Sensore di temperatura

public:
  Scheduler()
    : userDetector(2, 500), 
      levelDetector(A0, 100),
      display(0x27, 16, 2), 
      openButton(3, 500),
      closeButton(4, 500),
      ledGreen(5),
      ledRed(6),
      tempSensor(A1, 100)
  {
    door.attach(9);
  }

  void init(int basePeriod);  
  bool addTask(Task* task);  
  void schedule();
};

#endif