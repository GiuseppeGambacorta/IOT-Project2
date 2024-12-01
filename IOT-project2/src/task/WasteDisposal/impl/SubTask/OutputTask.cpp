#include "../../api/subTask/OutputTask.h"
#include "Components/Display/Api/Display.h"

OutputTask::OutputTask (
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed)
:
    ledGreen(ledGreen),
    ledRed(ledRed){}

void OutputTask::tick(){

    ledGreen.update();
    ledRed.update();
}

void OutputTask::reset(){

}

