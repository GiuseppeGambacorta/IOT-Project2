#include "../../api/subTask/StdExecTask.h"

#include "avr/sleep.h"
#include "EnableInterrupt.h"


StdExecTask ::StdExecTask(Door& door,
                          Display& display,
                          DigitalInput& openButton,
                          DigitalInput& closeButton,
                          DigitalOutput& ledGreen,
                          DigitalOutput& ledRed,
                          Pir& userDetector)
    : door(door),
      display(display),
      openButton(openButton),
      closeButton(closeButton),
      ledGreen(ledGreen),
      ledRed(ledRed),
      userDetector(userDetector){
        this->state = READY;
        this->userStatus = false;
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
        openTimer.active(true);
        state = OPEN;
    }
}

void StdExecTask ::homingOpen(){
    closeTimer.active(true);
    if (door.isClosed()){
        door.open();
    }
    display.clear();
    display.on();
    display.write("PRESS CLOSE WHEN YOU'RE DONE");
}

void StdExecTask ::execOpen(){
    homingOpen();
    if (closeButton.isActive() || closeTimer.isTimeElapsed()){
        closeTimer.active(false);
        closeTimer.reset();
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

    Serial.println("openButton: " + (String)openButton.isActive());
    Serial.println("closeButton: " + (String)closeButton.isActive());
    Serial.println("userDetector: " + (String)userDetector.isDetected());

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

    Serial.println("State: " + (String)state);
}

void StdExecTask ::reset(){
    this->userTimer.reset();
    this->closeTimer.reset();
    this->openTimer.reset();
    this->active = true;
    this->state = READY;
}