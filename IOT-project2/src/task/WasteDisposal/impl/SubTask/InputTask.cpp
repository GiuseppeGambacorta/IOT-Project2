#include "../../api/subTask/InputTask.h"

InputTask::InputTask(
                     DigitalInput& openButton, 
                     DigitalInput& closeButton) 
    : 
    openButton(openButton), 
    closeButton(closeButton){}

void InputTask::tick(){

    openButton.update();
    closeButton.update();
}

void InputTask::reset(){
    
}

