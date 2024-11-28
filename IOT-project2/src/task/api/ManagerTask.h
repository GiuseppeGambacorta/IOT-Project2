#ifndef __MANAGERTASK__
#define __MANAGERTASK__

#include "task/api/Task.h"
#include "ArduinoStandardLibrary.h"
#include "task/TasksType.h"

#define MAX_TASKS 10 //da rendere globale

#define LEVEL_MAX 100
#define TEMP_MAX 100

class ManagerTask : public Task {

private:
    AnalogInput levelDetector;
    AnalogInput tempSensor;
    DigitalInput userDetector;
    DigitalInput openButton;
    DigitalInput closeButton;
    Task* taskList[MAX_TASKS];
    
public:
    ManagerTask(AnalogInput levelDetector,
                AnalogInput tempSensor,
                DigitalInput userDetector, 
                DigitalInput openButton, 
                DigitalInput closeButton,
                Task* taskList[MAX_TASKS]);
    void tick();
    void tick();
    void reset();
};

#endif