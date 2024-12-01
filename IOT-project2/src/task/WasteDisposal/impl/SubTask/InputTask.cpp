#include "../../api/subTask/InputTask.h"

InputTask::InputTask(
                 Sonar& levelDetector,
                 Pir& userDetector,
                 TemperatureSensor& tempSensor,
                     DigitalInput& openButton, 
                     DigitalInput& closeButton) 
    : 
    levelDetector(levelDetector),
    userDetector(userDetector),
    tempSensor(tempSensor),
    openButton(openButton), 
    closeButton(closeButton){}

void InputTask::tick(){
    
    userDetector.update();
    levelDetector.update();
    tempSensor.update();
    openButton.update();
    closeButton.update();
}

void InputTask::reset(){
    
}

