#ifndef __STDEXECTASK__
#define __STDEXECTASK__

#include "task/api/Task.h"

enum StdExecState{
    READY,
    OPENING,
    OPEN,
    CLOSING
};

class StdExecTask : public Task {
    
private:
    StdExecState state;
    //add harware objects here
public:
    StdExecTask();
    void tick();
    void reset();
};

#endif 