#include "../../api/subTask/StdExecTask.h"
#include "Components/Display/Api/Display.h"


StdExecTask ::StdExecTask(Door& door,
                          Display& display,
                          DigitalInput& openButton,
                          DigitalInput& closeButton,
                          DigitalOutput& ledGreen,
                          DigitalOutput& ledRed,
                          Pir userDetector)
    : timer(OPEN_WAITING_TIME),
      door(door),
      display(display),
      openButton(openButton),
      closeButton(closeButton),
      ledGreen(ledGreen),
      ledRed(ledRed),
      userDetector(userDetector){
        this->state = READY;
        this->userStatus = true;
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
    display.on();
    display.write("PRESS OPEN TO INSERT WASTE");
}

void StdExecTask ::execReady(){
    homingReady();
    bool user = userDetector.isDetected();
    if (user){
        userTimer.reset();
    } else {
        userTimer.active(user);
    }
    if (userTimer.isTimeElapsed()) {
        state = SLEEP;
        userTimer.reset();
    }else if (openButton.isActive()){
        timer.active(true);
        state = OPEN;
    }
}

void StdExecTask ::homingOpen(){
    if (door.isClosed()){
        door.open();
    }
    display.clear();
    display.on();
    display.write("PRESS CLOSE WHEN YOU'RE DONE");
}

void StdExecTask ::execOpen(){
    homingOpen();
    if (closeButton.isActive() || timer.isTimeElapsed()){
        timer.active(false);
        timer.reset();
        state = READY;
    }
}

void StdExecTask ::homingSleep(){
    display.off();
}

void wakeUp(){
}

void StdExecTask ::execSleep(){
    homingSleep();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    enableInterrupt(userDetector.getPin(), wakeUp, HIGH);
    sleep_mode();
    disableInterrupt(userDetector.getPin());
    sleep_disable();
    display.on();
    state = READY;
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
    case SLEEP:
        execSleep();
        break;
    }
}

void StdExecTask ::reset(){
    this->timer.reset();
    this->active = true;
    this->state = READY;
}