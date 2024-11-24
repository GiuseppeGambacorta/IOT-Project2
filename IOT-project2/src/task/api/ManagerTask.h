#ifndef __MANAGERTASK__
#define __MANAGERTASK__

#include "task/api/Task.h"
#include "ArduinoStandardLibrary.h"
#include "task/TasksType.h"

#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"

#define MAX_TASKS 10 //da rendere globale

#define LEVEL_MAX 100
#define TEMP_MAX 100

class ManagerTask : public Task {

private:
    Sonar levelDetector;
    TemperatureSensor tempSensor;
    Pir userDetector;
    Task* taskList[MAX_TASKS];
    
public:
    ManagerTask(Sonar levelDetector,
                TemperatureSensor tempSensor,
                Pir userDetector,
                Task* taskList[MAX_TASKS]);

    void tick() override;
    void reset() override;
};

#endif