#include "task/api/StdExecTask.h"


StdExecTask ::StdExecTask(Door& door,
                          LiquidCrystal_I2C& display,
                          DigitalInput& openButton,
                          DigitalInput& closeButton,
                          DigitalOutput& ledGreen,
                          DigitalOutput& ledRed)
    : door(door),
      display(display),
      openButton(openButton),
      closeButton(closeButton),
      ledGreen(ledGreen),
      ledRed(ledRed),
      timer(OPEN_WAITING_TIME){
        this->type = STD_EXEC;
        this->state = READY;
}

void StdExecTask ::homingReady(){
    if (!ledGreen.isActive()){
        ledGreen.turnOn();
    }
    if (ledRed.isActive()){
        ledRed.turnOff();
    }
    if (door.isOpened()){
        door.close();
    }
    display.clear();
    display.setCursor(0, 0);
    display.print("PRESS OPEN TO INSERT WASTE");
}

void StdExecTask ::execReady(){
    homingReady();
    if (openButton.isActive()){
        timer.active(true);
        state = OPEN;
    }
}

void StdExecTask ::homingOpen(){
    if (door.isClosed()){
        door.open();
    }
    display.clear();
    display.setCursor(0, 0);
    display.print("PRESS CLOSE WHEN YOU'RE DONE");
}

void StdExecTask ::execOpen(){
    homingOpen();
    if (closeButton.isActive() || timer.isTimeElapsed()){
        timer.active(false);
        timer.reset();
        state = READY;
    }
}

void StdExecTask ::tick(){
    switch (state)
    {
    case READY:
        execReady();
        break;
    case OPEN:
        execOpen();
        break;
    }
}

void StdExecTask ::reset(){
    state = READY;
}