#pragma once

#include "task/api/Task.h"
#include "task/TasksType.h"

#include "Components/Door/Api/Door.h"
#include <LiquidCrystal_I2C.h>
#include "ArduinoStandardLibrary.h"

class ProvaGiuseppe : public Task {
private:
    Door& door;
    DigitalInput& button;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;

public:
    ProvaGiuseppe(Door& door, 
              DigitalInput& button, 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed) : door(door), button(button), ledGreen(ledGreen), ledRed(ledRed) {}
    void tick() override {

        if (button.isActive()) {
            door.open();
            ledGreen.turnOn();
            ledRed.turnOff();
        } else if (door.isOpened()) {
            door.close();
            ledGreen.turnOff();
            ledRed.turnOn();
        }

    }
    void reset() override {}
};


class ProvaGiuseppeAllarm : public Task {
private:
    Door& door;
    DigitalOutput& ledGreen;
    DigitalOutput& ledRed;

public:
    ProvaGiuseppeAllarm(Door& door, 
              DigitalOutput& ledGreen, 
              DigitalOutput& ledRed) : door(door),  ledGreen(ledGreen), ledRed(ledRed) {}
    void tick() override {

        door.empty();
        ledGreen.turnOn();
        ledRed.turnOn();

    }
    void reset() override {}
};

