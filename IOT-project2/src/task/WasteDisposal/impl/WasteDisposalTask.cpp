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
                empty = ServiceLocator::getSerialManagerInstance().getvar(1);
                fire = ServiceLocator::getSerialManagerInstance().getvar(0);
            }

void WasteDisposalTask::tick() {
    double level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();

    switch (state){
    case STD_EXEC:
                ServiceLocator::getSerialManagerInstance().addEventMessage("STD_EXEC");

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
            tempTimer.reset();
            state = WasteDisposalState::TEMP_ALLARM;
        }
        break;
    case LVL_ALLARM:
        if (*empty == 1) {
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
            tempTimer.reset();
            state = WasteDisposalState::TEMP_ALLARM;
        }
        break;
    case TEMP_ALLARM:
        ServiceLocator::getSerialManagerInstance().addEventMessage("TEMPERATURE ENTER");
        if ( *fire == 1) {
            tempTimer.reset();
            state = WasteDisposalState::TEMP_TIME;
        }
    case LVL_TIME:
        if ( *empty == 0) {
            state = WasteDisposalState::STD_EXEC;
        }
        break;
    /*
        if (emptyTimer.isTimeElapsed()) {
            emptyTimer.reset();
            *empty = 0;
            state = WasteDisposalState::STD_EXEC;
        }*/
    case TEMP_TIME:
        ServiceLocator::getSerialManagerInstance().addEventMessage("TEMPERATURE EXIT");

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
            alarmLevelTask.setActive(true);
            alarmTempTask.setActive(false);
            break;
        case TEMP_TIME:
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
