#include "task/api/ManagerTask.h"

BidoneTask::BidoneTask(Sonar& levelDetector,
                         TemperatureSensor& tempSensor,
                         Pir& userDetector,
                         DigitalInput& openButton,
                         DigitalInput& closeButton,
                         Door& Door,
                         LiquidCrystal_I2C& display,
                         DigitalOutput& ledGreen,
                         DigitalOutput& ledRed)
    : levelDetector(levelDetector),
      tempSensor(tempSensor),
      userDetector(userDetector),
      openButton(openButton),
      closeButton(closeButton),
      door(door),
      display(display),
      ledGreen(ledGreen),
      ledRed(ledRed),
      InputTask(userDetector, levelDetector, tempSensor, openButton, closeButton),
     // StdExecTask(door, display, ledGreen, ledRed),
      OutputTask(door, display, ledGreen, ledRed) {
}

void BidoneTask::tick() {

    InputTask.tick();


    // allarm tick

    int level = levelDetector.readDistance();
    int temp = tempSensor.readTemperature();
    bool user = userDetector.isDetected();

    // Gestione degli allarmi e degli stati
    if (level < LEVEL_MAX) {
        levelAlarm = true;
    } else {
        levelAlarm = false;
    }

    tempTimer.active(temp > TEMP_MAX);
    if (tempTimer.isTimeElapsed()) {
        tempAlarm = true;
    } else {
        tempAlarm = false;
    }

    userTimer.active(user);
    if (userTimer.isTimeElapsed()) {
        userStatus = false;
    } else {
        userStatus = true;
    }

    switch (this->state)
    {
    case 0:
        ActualTask = InputTask;

        break;

    case 10:
        ActualTask = InputTask;

        if (levelAlarm) {
            state = 20;
        } else if (tempAlarm) {
            state = 30;
        } else if (!userStatus) {
            state = 40;
        } else {
            state = 10;
        }

        break;
    
    default:
        break;
    }

    ActualTask.tick();

    OutputTask.tick();
}

void ManagerTask::reset() {
    tempAlarm = false;
    levelAlarm = false;
    userStatus = true;

    tempTimer.reset();
    userTimer.reset();
}
