#include "../../api/subTask/OutputTask.h"
#include "Components/Display/Api/Display.h"

OutputTask::OutputTask (
                Door& door,
                Display& display,
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed)
    : door(door),
    display(display),
    ledGreen(ledGreen),
    ledRed(ledRed){}

void OutputTask::tick(){
    

    
    //display.write("Ciao");
    door.update();
    display.update("ciao");
    ledGreen.update();
    ledRed.update();
}

void OutputTask::reset(){

}

