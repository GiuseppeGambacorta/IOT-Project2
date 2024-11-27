#ifndef __MANAGERTASK__
#define __MANAGERTASK__

#include "Task.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "OutputTask.h"
#include "SleepTask.h"
#include "StdExecTask.h"
#include "InputTask.h"

#define MAX_TASKS 10 //da rendere globale

#define MAXTEMPTIME 10000
#define TSleep 10000
#define LEVEL_MAX 10
#define TEMP_MAX 100


struct BidoneCommunication
{
    bool alarm;
    int level;
};




class BidoneTask : public Task {

private:
    Sonar& levelDetector;
    TemperatureSensor& tempSensor;
    Pir& userDetector;
    DigitalInput& openButton;
    DigitalInput& closeButton;
    Door& door;
    LiquidCrystal_I2C& display;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;

    InputTask InputTask;
    StdExecTask StdExecTask;
    OutputTask OutputTask;

    Task& ActualTask;

    BidoneCommunication communication;
    unsigned int state;
    bool tempAlarm;
    bool levelAlarm;
    bool userStatus;

    Timer tempTimer = Timer(MAXTEMPTIME);
    Timer userTimer = Timer(TSleep);
    
public:
    BidoneTask(Sonar& levelDetector,
                         TemperatureSensor& tempSensor,
                         Pir& userDetector,
                         DigitalInput& openButton,
                         DigitalInput& closeButton,
                         Door& door,
                         LiquidCrystal_I2C& display,
                         DigitalOutput& ledGreen,
                         DigitalOutput& ledRed);

    void tick() override;
    void reset() override;
};

#endif