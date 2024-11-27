#include "task/api/BidoneTask.h"






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
      ledRed(ledRed) {}
    //  InputTask(userDetector, levelDetector, tempSensor, openButton, closeButton) 
     // StdExecTask(door, display, ledGreen, ledRed),
     // OutputTask(door, display, ledGreen, ledRed) 

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
    case BidoneState::Homing:
        //ActualTask = InputTask
        if homing.done() {
            homing.reset();
            state = 10;
        }

        break;

    case BidoneState::Normal:
        ActualTask = InputTask;

        if (levelAlarm) {
            state = BidoneState::LevelAlarm;
        } else if (tempAlarm) {
            state = BidoneState::TempAlarm;
        } else if (!userStatus) {
            state = BidoneState::Sleep;
        }

        break;

    case BidoneState::LevelAlarm:
        ActualTask = InputTask;

        if (!levelAlarm) {
            state = BidoneState::Homing 
        }

        break;

    case BidoneState::TempAlarm:
        ActualTask = InputTask;

        if (!tempAlarm) {
            state = BidoneState::Homing;
        }

        break;
    
    case BidoneState::Sleep:
        ActualTask = InputTask;

        if (userStatus) {
            state = BidoneState::Homing;
        }

        break;
    default:
        break;
    }

    ActualTask.tick();

    OutputTask.tick();
    
}

void BidoneTask::reset() {
    /*
    tempAlarm = false;
    levelAlarm = false;
    userStatus = true;

    tempTimer.reset();
    userTimer.reset();
    */
}
