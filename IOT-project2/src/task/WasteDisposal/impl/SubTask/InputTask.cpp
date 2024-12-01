#include "../../api/subTask/InputTask.h"

InputTask::InputTask(
                 Sonar& levelDetector,
                     DigitalInput& openButton, 
                     DigitalInput& closeButton) 
    : 
    levelDetector(levelDetector),
    openButton(openButton), 
    closeButton(closeButton){}

void InputTask::tick(){
    //Serial.println("InputTask");
    levelDetector.update();
    openButton.update();
    closeButton.update();
}

void InputTask::reset(){
    
}

