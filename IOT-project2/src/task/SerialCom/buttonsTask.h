#pragma once

#include <../Services/Services.h>
#include "./task/Task.h"
#include <ArduinoStandardLibrary.h>
#include "Components/Door/Api/Door.h"


class ButtonsTask : public Task {

private:
    
   
    int state = 0;
    SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();
    DigitalInput& openButton;
    DigitalInput& closeButton;
public:
    ButtonsTask(DigitalInput& openButton, DigitalInput& closeButton)
      : openButton(openButton), closeButton(closeButton) {        
      
    }

    void tick() override {

        if (openButton.isChanged() && openButton.isActive()) {
            serialManager.addEventMessage("open button pressed");

        }
        
        if (closeButton.isChanged() && closeButton.isActive()) {
            serialManager.addEventMessage("close button pressed");

        }

        if (closeButton.isChanged() && !closeButton.isActive()) {
            serialManager.addEventMessage("close button released");
        }

        if (openButton.isChanged() && !openButton.isActive()) {
            serialManager.addEventMessage("open button released");
        }

       
    }
    void reset() override {
        ;
    }
};
