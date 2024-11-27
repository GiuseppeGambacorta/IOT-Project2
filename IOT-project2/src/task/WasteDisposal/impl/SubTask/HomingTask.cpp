#include "../../api/subTask/HomingTask.h"


HomingTask::HomingTask(Door& door,
                          LiquidCrystal_I2C& display,
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