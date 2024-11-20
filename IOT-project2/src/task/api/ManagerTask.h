#ifndef __MANAGERTASK__
#define __MANAGERTASK__

#include "task/api/Task.h"

class ManagerTask : public Task {

private:
    //add harware objects here
public:
    ManagerTask();
    void tick();
    void reset();
};

#endif