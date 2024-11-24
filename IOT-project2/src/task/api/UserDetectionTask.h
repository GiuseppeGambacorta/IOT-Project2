#ifndef __USERDETECTIONTASK__
#define __USERDETECTIONTASK__

#include "Task.h"
#include "Pir.h"

class UserDetectionTask : public Task {
  Pir& pir;
  enum {NO_USER, USER_DETECTED} state;

  public:

    UserDetectionTask(Pir& sensor);
    void tick();
    void reset();
    int getState();
};

#endif