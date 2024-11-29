#include "../api/WasteDisposalTask.h"



WasteDisposalTask::WasteDisposalTask(
                      EmptyBinTask& emptyBinTask,
                      HomingTask& homingTask,
                      SleepTask& sleepTask,
                      StdExecTask& stdExecTask
                     )
            : emptyBinTask(emptyBinTask),
              homingTask(homingTask),
              sleepTask(sleepTask),
              stdExecTask(stdExecTask)
     {}


void WasteDisposalTask::tick() {
    /*
    int level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();
    bool user = userDetector.isDetected();

    this->homingTask.active(false);
    this->stdExecTask.active(false);
    this->sleepTask.active(false);
    this->emptyBinTask.active(false);
    */
}

void WasteDisposalTask::reset() {
    this->stdExecTask.reset();
    this->emptyBinTask.reset();
    this->sleepTask.reset();
    this->state = WasteDisposalState::Homing;
}
