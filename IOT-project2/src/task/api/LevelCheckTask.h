#ifndef __LEVELCHECKTASK__
#define __LEVELCHECKTASK__

#include "Task.h"
#include "Sonar.h"

class LevelCheckTask : public Task {
  Sonar& sonar;
  enum {OK, HIGH_LEVEL} state;

  public:

    LevelCheckTask(Sonar& sensor);
    void tick();
    void reset();
};

#endif