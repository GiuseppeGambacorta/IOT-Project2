#include "task/api/InputTask.h"

InputTask::InputTask(Pir& userDetector, 
                     Sonar& levelDetector, 
                     TemperatureSensor& tempSensor,  
                     DigitalInput& openButton, 
                     DigitalInput& closeButton) 
    : userDetector(userDetector), 
    levelDetector(levelDetector), 
    tempSensor(tempSensor), 
    openButton(openButton), 
    closeButton(closeButton){
    this->type = IN;
}

void InputTask::tick(){
    userDetector.update();
    levelDetector.update();
    tempSensor.update();
    openButton.update();
    closeButton.update();
}

void InputTask::reset(){
    
}

