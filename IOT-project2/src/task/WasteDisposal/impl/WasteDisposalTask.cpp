#include "../api/WasteDisposalTask.h"






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
      door(Door),
      display(display),
      ledGreen(ledGreen),
      ledRed(ledRed),
      alarmLevelTask(Door, display, ledGreen, ledRed),
      alarmTempTask(ledGreen, ledRed, display, Door),
      emptyBinTask(Door, display, ledGreen, ledRed),
      homingTask(Door, display, openButton, closeButton, ledGreen, ledRed),
      inputTask(userDetector, levelDetector, tempSensor, openButton, closeButton),
      outputTask(Door, display, ledGreen, ledRed),
      sleepTask(userDetector, levelDetector, Door, display, openButton, closeButton, ledGreen, ledRed, tempSensor),
      stdExecTask(Door, display, openButton, closeButton, ledGreen, ledRed) {}


void WasteDisposalTask::tick() {
    
    this->inputTask.tick();

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
        this->ActualTask = this->homingTask;
        
        /*
        if homing.done() {
            homing.reset();
            state = 10;
        }
        */

        break;

    case WasteDisposalState::Normal:
        this->ActualTask = this->stdExecTask;

        if (!userStatus) {
            state = WasteDisposalState::Sleep;
        } else if (tempAlarm) {
            state = WasteDisposalState::TempAlarm;
        } else if (levelAlarm) {
            state = WasteDisposalState::LevelAlarm;
        }

        break;

        case WasteDisposalState::LevelAlarm:
        this->ActualTask = this->alarmLevelTask;

        if (!levelAlarm) {
            state = WasteDisposalState::Homing;
        }

        break;

    case WasteDisposalState::TempAlarm:
        this->ActualTask = this->alarmTempTask;

        if (!tempAlarm) {
            state = WasteDisposalState::Homing;
        }

        break;
    
    case WasteDisposalState::Sleep:
        this->ActualTask = this->sleepTask;

        if (userStatus) {
            state = WasteDisposalState::Homing;
        }

        break;
    default:
        break;
    }

    this->ActualTask.tick();
    this->outputTask.tick();
    
}

void WasteDisposalTask::reset() {
   this->inputTask.reset();
    this->stdExecTask.reset();
    this->outputTask.reset();
    this->alarmLevelTask.reset();
    this->alarmTempTask.reset();
    this->emptyBinTask.reset();
    this->sleepTask.reset();
    this->ActualTask.reset();
    this->state = WasteDisposalState::Homing;
}
