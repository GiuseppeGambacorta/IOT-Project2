#ifndef __MANAGERTASK__
#define __MANAGERTASK__

#include "task/api/Task.h"
#include "ArduinoStandardLibrary.h"

class ManagerTask : public Task {

private:
    
public:
    ManagerTask();
    void tick();
    void tick(DigitalInput userDetector, DigitalInput openButton, DigitalInput closeButton);
    void reset();
};

#endif