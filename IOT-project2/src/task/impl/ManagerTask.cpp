#include "task/api/ManagerTask.h"

ManagerTask::ManagerTask(AnalogInput levelDetector,
                         AnalogInput tempSensor,
                         DigitalInput userDetector, 
                         DigitalInput openButton, 
                         DigitalInput closeButton,
                         Task* taskList[MAX_TASKS])
    : levelDetector(levelDetector),
      tempSensor(tempSensor), 
      userDetector(userDetector), 
      openButton(openButton), 
      closeButton(closeButton)
{
    this->type = MANAGER;
    for (int i = 0; i < MAX_TASKS; i++) {
        this->taskList[i] = taskList[i];
    }
}
void ManagerTask::tick() {

    int level = levelDetector.getValue();
    int temp = tempSensor.getValue();
    bool user = userDetector.isActive();
    bool openPressed = openButton.isActive();
    bool closePressed = closeButton.isActive();

    //logica di gestione

}

