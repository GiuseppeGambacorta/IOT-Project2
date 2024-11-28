#ifndef __USERDETECTION__
#define __USERDETECTION__

#include "../../../Task.h"
#include "Components/Pir/api/Pir.h"

class UserDetection : public Task {
  Pir& pir;
  enum {NO_USER, USER_DETECTED} state;

  public:

    UserDetection(Pir& sensor);
    void tick();
    void reset();
    int getState();
};

#endif