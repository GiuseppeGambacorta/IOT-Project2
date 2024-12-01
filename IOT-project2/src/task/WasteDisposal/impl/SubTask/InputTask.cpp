#include "../../api/subTask/InputTask.h"

InputTask::InputTask(
           //          TemperatureSensor& tempSensor,
                     DigitalInput& openButton, 
                     DigitalInput& closeButton) 
    : 
    openButton(openButton), 
    closeButton(closeButton){}

void InputTask::tick(){

   // tempSensor.update();
    openButton.update();
    closeButton.update();
}

void InputTask::reset(){
    
}

