
#include <Arduino.h>

#ifndef SERVICES_H
#define SERVICES_H


/* Interface for TimeKeeper */
class ITimeKeeper {
protected:
    ITimeKeeper();
    unsigned long currentTime;

public:

  virtual ~ITimeKeeper() = default; // default destructor for all derived classes
  static ITimeKeeper& getInstance();
  unsigned long getCurrentTime();
  virtual void update() = 0;

  ITimeKeeper(const ITimeKeeper&) = delete;  // TimeKeeper tk2 = tk1;  // NO
  void operator=(const ITimeKeeper&) = delete; // tk2 = tk1; // NO
};


/* Class that uses Millis() */
class TimeKeeper : public ITimeKeeper {
private:
    TimeKeeper();

public:
    static ITimeKeeper& getInstance();
    void update() override;
};

/* Class that uses a Mock Time for tests */
class MockTimeKeeper : public ITimeKeeper {
private:
    MockTimeKeeper();

public:
    static ITimeKeeper& getInstance();
    void update() override;
    void setTime(unsigned long newTime);
};


class ServiceLocator {

    private:
    inline static ITimeKeeper* timeKeeper = &TimeKeeper::getInstance();

    public:
    static void setTimeKeeperInstance(ITimeKeeper* newTimeKeeper){
        timeKeeper = newTimeKeeper;
    }

    static ITimeKeeper& getTimeKeeperInstance(){
        return *timeKeeper;
    }

};

#endif