
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
  //void operator=(const ITimeKeeper&) = delete; // tk2 = tk1; // NO
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


/*  Input Services  */

class IInputKeeper {
protected:
    IInputKeeper();
    bool digitalPins[NUM_DIGITAL_PINS]; // digital pin + analog pin, because analog pins can be used as digital
    int analogPins[NUM_ANALOG_INPUTS];

public:

  virtual ~IInputKeeper() = default; // default destructor for all derived classes
  static IInputKeeper& getInstance();
  bool getDigitalPinState(unsigned int pin);
  unsigned int getAnalogPinValue(unsigned int pin);
  virtual void update() = 0;

  IInputKeeper(const IInputKeeper&) = delete;  // IInputKeeper tk2 = tk1;  // NO

};


class RealInputKeeper : public IInputKeeper {

    private:
        RealInputKeeper();
    public:
        static IInputKeeper& getInstance();
        void update() override;
};



class MockInputKeeper : public IInputKeeper {

    private:
        MockInputKeeper();
    public:
        static IInputKeeper& getInstance();
        void update() override;
        void setDigitalPinState(unsigned int pin, bool state);
        void setAnalogPinValue(unsigned int pin, unsigned int value);
};


class ServiceLocator {

    private:
        static ITimeKeeper* timeKeeper; 
        static IInputKeeper* inputKeeper;

    public:
        static void setTimeKeeperInstance(ITimeKeeper& newTimeKeeper){
            timeKeeper = &newTimeKeeper;
        }

        static ITimeKeeper& getTimeKeeperInstance(){
            return *timeKeeper;
        }


        static void setInputKeeperInstance(IInputKeeper& newInputKeeper){
            inputKeeper = &newInputKeeper;
        }

        static IInputKeeper& getInputKeeperInstance(){
            return *inputKeeper;
        }

};










#endif