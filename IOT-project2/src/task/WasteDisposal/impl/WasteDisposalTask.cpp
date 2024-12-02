#include "../api/WasteDisposalTask.h"

#define MAXTEMPTIME 10000
#define TSleep 10000
#define TEmpty 3000
double maxLevel = 0.3;
int maxTemp = 100;

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
            emptyTimer(Timer(TEmpty)),
            levelDetector(levelDetector),
            tempSensor(tempSensor){
                int *empty = ServiceLocator::getSerialManagerInstance().getvar(1);
                int *fire = ServiceLocator::getSerialManagerInstance().getvar(0);
            }

void WasteDisposalTask::tick() {
    double level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();

    switch (state){
    case STD_EXEC:
        if (level <= maxLevel) {
            state = WasteDisposalState::LVL_ALLARM;
        }
        if (temp >= maxTemp) {
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
        if (level <= maxLevel && *empty == 1) {
            emptyTimer.active(true);
            state = WasteDisposalState::LVL_TIME;
        }
        if (temp >= maxTemp) {
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
        if ( *fire == 1) {
            tempTimer.active(false);
            tempTimer.reset();
            state = WasteDisposalState::TEMP_TIME;
        }
    case LVL_TIME:
        if (emptyTimer.isTimeElapsed()) {
            emptyTimer.reset();
            state = WasteDisposalState::STD_EXEC;
        }
    case TEMP_TIME:
        if ( *fire == 0) {
            state = WasteDisposalState::STD_EXEC;
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
        case LVL_TIME:
            stdExecTask.setActive(false);
            alarmLevelTask.setActive(active);
            alarmTempTask.setActive(false);
            break;
        case TEMP_TIME:
            stdExecTask.setActive(false);
            alarmLevelTask.setActive(false);
            alarmTempTask.setActive(true);
            break;
    }

    Serial.println("stdExecTask: " + (String)stdExecTask.isActive());
    Serial.println("alarmLevelTask: " + (String)alarmLevelTask.isActive());
    Serial.println("alarmTempTask: " + (String)alarmTempTask.isActive());
}

void WasteDisposalTask::reset() {
    state = WasteDisposalState::STD_EXEC;
    //tempTimer.reset();
    stdExecTask.setActive(true);
    alarmLevelTask.setActive(false);
    alarmTempTask.setActive(false);
}
