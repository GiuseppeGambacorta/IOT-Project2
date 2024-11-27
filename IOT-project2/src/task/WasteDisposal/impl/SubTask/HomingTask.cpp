#include "../../api/subTask/HomingTask.h"
#include "Components/Display/Api/Display.h"


HomingTask::HomingTask(Door& door,
                          Display& display,
                          DigitalInput& openButton,
                          DigitalInput& closeButton,
                          DigitalOutput& ledGreen,
                          DigitalOutput& ledRed) :
                            door(door),
                            display(display),
                            openButton(openButton),
                            closeButton(closeButton),
                            ledGreen(ledGreen),
                            ledRed(ledRed) {}


void HomingTask ::tick(){

}

void HomingTask ::reset(){

}