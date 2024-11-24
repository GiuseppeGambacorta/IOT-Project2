#include "task/api/InputTask.h"

void InputTask::tick(){
    userDetector.update();
    levelDetector.update();
    tempSensor.update();
    openButton.update();
    closeButton.update();
}

