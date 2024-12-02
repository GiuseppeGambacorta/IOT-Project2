#pragma once

#include <../Services/Services.h>
#include "./task/Task.h"


class SerialInputTask : public Task {

private:
    SerialManager& serialManager;
    
public:
    SerialInputTask() : serialManager(ServiceLocator::getSerialManagerInstance()) {}

    void tick() override {
        if (!serialManager.isConnectionEstablished()){
            serialManager.doHandshake();
        } else {
            serialManager.getData();
        }
    }
    void reset() override {
        ;
    }
};
