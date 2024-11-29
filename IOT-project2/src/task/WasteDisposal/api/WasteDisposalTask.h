#ifndef __WASTE_DISPOSAL_TASK__
#define __WASTE_DISPOSAL_TASK__

#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"

#include "subTask/StdExecTask.h"
#include "subTask/AlarmLevelTask.h"
#include "subTask/AlarmTempTask.h"

#define MAXTEMPTIME 10000
#define TSleep 10000
#define LEVEL_MAX 10
#define TEMP_MAX 100


enum WasteDisposalState {
    STD_EXEC,
    LVL_ALLARM,
    TEMP_ALLARM
};



class WasteDisposalTask : public Task {

private:
    StdExecTask& stdExecTask;
    AlarmLevelTask& alarmLevelTask;
    AlarmTempTask& alarmTempTask;

    WasteDisposalState state;

    Timer tempTimer;

    Sonar levelDetector;
    TemperatureSensor tempSensor;
    
public:
    WasteDisposalTask(
                    StdExecTask& stdExecTask,
                    AlarmLevelTask& alarmLevelTask,
                    AlarmTempTask& alarmTempTask,
                    Sonar& levelDetector,
                    TemperatureSensor& tempSensor);

    void tick() override; 
    void reset() override;
};

#endif