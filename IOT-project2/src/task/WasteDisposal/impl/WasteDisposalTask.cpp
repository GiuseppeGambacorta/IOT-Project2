#include "task/WasteDisposal/api/WasteDisposalTask.h"

WasteDisposalTask::WasteDisposalTask(StdExecTask& stdExecTask,
                                     AlarmLevelTask& alarmLevelTask,
                                     AlarmTempTask& alarmTempTask,
                                     Sonar& levelDetector,
                                     TemperatureSensor& tempSensor)
            :stdExecTask(stdExecTask),
            alarmLevelTask(alarmLevelTask),
            alarmTempTask(alarmTempTask),
            state(WasteDisposalState::STD_EXEC),
            tempTimer(Timer(MAXTEMPTIME)),
            levelDetector(levelDetector),
            tempSensor(tempSensor){}

void WasteDisposalTask::tick() {
    int level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();

    switch (state){
    case STD_EXEC:
        if (level >= LEVEL_MAX) {
            state = WasteDisposalState::LVL_ALLARM;
        }
        if (temp >= TEMP_MAX) {
            tempTimer.active(true);
        } else {
            tempTimer.active(false);
            tempTimer.reset();
        }
        if (tempTimer.isTimeElapsed()) {
            state = WasteDisposalState::TEMP_ALLARM;
        }
        break;
    case LVL_ALLARM:
        if (level < LEVEL_MAX) {
            state = WasteDisposalState::STD_EXEC;
        }
        if (temp > TEMP_MAX) {
            tempTimer.active(true);
        } else {
            tempTimer.active(false);
            tempTimer.reset();
        }
        if (tempTimer.isTimeElapsed()) {
            state = WasteDisposalState::TEMP_ALLARM;
        }
        break;
    case TEMP_ALLARM:
        if (temp < TEMP_MAX) {
            tempTimer.active(false);
            tempTimer.reset();
            state = WasteDisposalState::STD_EXEC;
        }
        if (level >= LEVEL_MAX) {
            state = WasteDisposalState::LVL_ALLARM;
        }
        break;
    }

    switch (state){
        case STD_EXEC:
            stdExecTask.setActive(true);
            alarmLevelTask.setActive(false);
            alarmTempTask.setActive(false);
            break;
        case LVL_ALLARM:
            stdExecTask.setActive(false);
            alarmLevelTask.setActive(true);
            alarmTempTask.setActive(false);
            break;
        case TEMP_ALLARM:
            stdExecTask.setActive(false);
            alarmLevelTask.setActive(false);
            alarmTempTask.setActive(true);
            break;
    }
}

void WasteDisposalTask::reset() {
    state = WasteDisposalState::STD_EXEC;
    tempTimer.reset();
    stdExecTask.setActive(true);
    alarmLevelTask.setActive(false);
    alarmTempTask.setActive(false);
}
