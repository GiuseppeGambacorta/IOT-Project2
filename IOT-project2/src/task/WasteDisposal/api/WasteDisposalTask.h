#pragma once




#include "../../Task.h"
#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"
#include "Components/Display/Api/Display.h"
#include "subTask/OutputTask.h"
#include "subTask/SleepTask.h"
#include "subTask/StdExecTask.h"
#include "subTask/InputTask.h"
#include "subTask/HomingTask.h"
#include "subTask/EmptyBinTask.h"
#include "subTask/AlarmLevelTask.h"
#include "subTask/AlarmTempTask.h"


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
    Display& display;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;


    AlarmLevelTask alarmLevelTask;
    AlarmTempTask alarmTempTask;
    EmptyBinTask emptyBinTask;
    HomingTask homingTask;
    InputTask inputTask;
    OutputTask outputTask;
    SleepTask sleepTask;
    StdExecTask stdExecTask;




    Task& ActualTask = homingTask;

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
                         Display& display,
                         DigitalOutput& ledGreen,
                         DigitalOutput& ledRed);

    void tick() override;
    void reset() override;
};
