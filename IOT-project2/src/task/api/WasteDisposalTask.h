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
#include "EmptyBinTask.h"
#include "AlarmTempTask.h"
#include "AlarmLevelTask.h"


#define MAX_TASKS 10 //da rendere globale

#define MAXTEMPTIME 10000
#define TSleep 10000
#define LEVEL_MAX 10
#define TEMP_MAX 100


struct WasteDisposalCommunication
{
    bool alarm;
    int level;
};


enum WasteDisposalState {
    Homing = 0,
    Normal = 10,
    LevelAlarm = 20,
    TempAlarm = 30,
    Sleep = 40

};



class WasteDisposalTask : public Task {

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

    InputTask inputTask;
    StdExecTask stdExecTask;

    EmptyBinTask emptyBinTask;
    OutputTask outputTask;
    SleepTask sleepTask;
    Task& ActualTask;

    WasteDisposalState state = WasteDisposalState::Homing;
    WasteDisposalCommunication communication;
    
    bool tempAlarm;
    bool levelAlarm;
    bool userStatus;

    Timer tempTimer = Timer(MAXTEMPTIME);
    Timer userTimer = Timer(TSleep);
    
public:
    WasteDisposalTask(Sonar& levelDetector,
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