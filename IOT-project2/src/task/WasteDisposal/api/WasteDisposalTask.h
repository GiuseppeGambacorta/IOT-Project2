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
   


    EmptyBinTask& emptyBinTask;
    HomingTask& homingTask;
    SleepTask& sleepTask;
    StdExecTask& stdExecTask;


    WasteDisposalState state = WasteDisposalState::Homing;
    
    bool tempAlarm;
    bool levelAlarm;
    bool userStatus;

    Timer tempTimer = Timer(MAXTEMPTIME);
    Timer userTimer = Timer(TSleep);
    
public:
    WasteDisposalTask(
                      EmptyBinTask& emptyBinTask,
                      HomingTask& homingTask,
                      SleepTask& sleepTask,
                      StdExecTask& stdExecTask
                     );

    void tick() override;
    void reset() override;
};
