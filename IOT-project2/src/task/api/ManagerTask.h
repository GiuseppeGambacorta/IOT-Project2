#ifndef __MANAGERTASK__
#define __MANAGERTASK__

#include "Task.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"

#define MAX_TASKS 10 //da rendere globale

#define MAXTEMPTIME 10000
#define TSleep 10000
#define LEVEL_MAX 10
#define TEMP_MAX 100

class ManagerTask : public Task {

private:
    Sonar& levelDetector;
    TemperatureSensor& tempSensor;
    Pir& userDetector;
    Task* taskList[MAX_TASKS];
    bool tempAlarm;
    bool levelAlarm;
    bool userStatus;
    Timer tempTimer = Timer(MAXTEMPTIME);
    Timer userTimer = Timer(TSleep);
    
public:
    ManagerTask(Sonar& levelDetector,
                TemperatureSensor& tempSensor,
                Pir& userDetector,
                Task* taskList[MAX_TASKS]);

    void tick() override;
    void reset() override;
};

#endif