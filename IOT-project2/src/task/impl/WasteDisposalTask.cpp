#include "task/api/WasteDisposalTask.h"






WasteDisposalTask::WasteDisposalTask(Sonar& levelDetector,
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

void WasteDisposalTask::tick() {
    
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
    case WasteDisposalState::Homing:
        //ActualTask = InputTask
        if homing.done() {
            homing.reset();
            state = 10;
        }

        break;

    case WasteDisposalState::Normal:
        ActualTask = InputTask;

        if (levelAlarm) {
            state = WasteDisposalState::LevelAlarm;
        } else if (tempAlarm) {
            state = WasteDisposalState::TempAlarm;
        } else if (!userStatus) {
            state = WasteDisposalState::Sleep;
        }

        break;

    case WasteDisposalState::LevelAlarm:
        ActualTask = InputTask;

        if (!levelAlarm) {
            state = WasteDisposalState::Homing 
        }

        break;

    case WasteDisposalState::TempAlarm:
        ActualTask = InputTask;

        if (!tempAlarm) {
            state = WasteDisposalState::Homing;
        }

        break;
    
    case WasteDisposalState::Sleep:
        ActualTask = InputTask;

        if (userStatus) {
            state = WasteDisposalState::Homing;
        }

        break;
    default:
        break;
    }

    ActualTask.tick();

    OutputTask.tick();
    
}

void WasteDisposalTask::reset() {
    /*
    tempAlarm = false;
    levelAlarm = false;
    userStatus = true;

    tempTimer.reset();
    userTimer.reset();
    */
}
