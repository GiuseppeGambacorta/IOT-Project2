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
    

    String message = "Ciao";
    display.write(message);
    door.update();
    display.update();
    ledGreen.update();
    ledRed.update();
}

void OutputTask::reset(){

}

