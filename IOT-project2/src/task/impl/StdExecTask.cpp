#include "task/api/StdExecTask.h"


StdExecTask ::StdExecTask(Door door,
                          LiquidCrystal_I2C display,
                          DigitalInput openButton,
                          DigitalInput closeButton,
                          DigitalOutput ledGreen,
                          DigitalOutput ledRed)
    : door(door),
      display(display),
      openButton(openButton),
      closeButton(closeButton),
      ledGreen(ledGreen),
      ledRed(ledRed){
    this->type = STD_EXEC;
    this->state = READY;
}

void StdExecTask ::tick(){
    switch (state)
    {
    case READY:
        // TODO: implement
        break;
    case OPENING:
        // TODO: implement
        break;
    case OPEN:
        // TODO: implement
        break;
    case CLOSING:
        // TODO: implement
        break;
    }
}

void StdExecTask ::reset(){
    state = READY;
}