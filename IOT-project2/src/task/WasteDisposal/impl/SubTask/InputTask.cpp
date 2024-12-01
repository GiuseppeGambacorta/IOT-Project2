#include "../../api/subTask/InputTask.h"

InputTask::InputTask(
                 Sonar& levelDetector,
                 Pir& userDetector,
                     DigitalInput& openButton, 
                     DigitalInput& closeButton) 
    : 
    levelDetector(levelDetector),
    userDetector(userDetector),
    openButton(openButton), 
    closeButton(closeButton){}

void InputTask::tick(){
    
    userDetector.update();
    levelDetector.update();
    openButton.update();
    closeButton.update();
}

void InputTask::reset(){
    
}

