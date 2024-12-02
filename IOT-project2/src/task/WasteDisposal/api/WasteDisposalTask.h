#ifndef __WASTE_DISPOSAL_TASK__
#define __WASTE_DISPOSAL_TASK__

#include "Components/Pir/Api/Pir.h"
#include "Components/Sonar/Api/Sonar.h"
#include "Components/Temperaturesensor/Api/TemperatureSensor.h"

#include "subTask/StdExecTask.h"
#include "subTask/AlarmLevelTask.h"
#include "subTask/AlarmTempTask.h"


enum WasteDisposalState {
    STD_EXEC,
    LVL_ALLARM,
    LVL_TIME,
    TEMP_ALLARM,
    TEMP_TIME
};

class WasteDisposalTask : public Task {

private:
    StdExecTask& stdExecTask;
    AlarmLevelTask& alarmLevelTask;
    AlarmTempTask& alarmTempTask;

    WasteDisposalState state;

    Timer tempTimer;
    Timer emptyTimer;

    Sonar& levelDetector;
    TemperatureSensor& tempSensor;

    int *empty;
    int *fire;
    
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