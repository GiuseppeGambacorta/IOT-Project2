#ifndef __LEVELCHECK__
#define __LEVELCHECK__

#include "../../../Task.h"
#include "Components/Sonar/api/Sonar.h"

class LevelCheck : public Task {
  Sonar& sonar;
  enum {OK, HIGH_LEVEL} state;

  public:

    LevelCheck(Sonar& sensor);
    void tick();
    void reset();
    int getState();
};

#endif