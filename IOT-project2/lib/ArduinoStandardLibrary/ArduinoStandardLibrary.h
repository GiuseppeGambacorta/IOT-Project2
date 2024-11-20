#include <Arduino.h>

#ifndef STANDARDLIBRARY_H
#define STANDARDLIBRARY_H


class ITimeKeeper {


protected:
    ITimeKeeper() : currentTime(0) {}
    unsigned long currentTime;


public:
  ITimeKeeper& getInstance();
  virtual void update() = 0;
  unsigned long getCurrentTime(){
    return currentTime;
  }

  ITimeKeeper(const ITimeKeeper&) = delete;  // TimeKeeper tk2 = tk1;  // NO
  void operator=(const ITimeKeeper&) = delete; // tk2 = tk1; // NO
};


class TimeKeeper : ITimeKeeper {
private:
    // Costruttore privato per il singleton
    TimeKeeper();
public:
    // Metodo per ottenere l'istanza singleton,l'istanza viene creata alla prima chiamata di getIstance
    static ITimeKeeper& getInstance() {
        static TimeKeeper instance;
        return instance;
    }

    void update() override;

    // Elimina i metodi di copia e assegnazione per evitare copie dell'istanza singleton
    TimeKeeper(const TimeKeeper&) = delete;  // TimeKeeper tk2 = tk1;  // NO
    void operator=(const TimeKeeper&) = delete; // tk2 = tk1; // NO
};


class MockTimeKeeper : ITimeKeeper {
private:
    // Costruttore privato per il singleton
    MockTimeKeeper();
public:
    // Metodo per ottenere l'istanza singleton,l'istanza viene creata alla prima chiamata di getIstance
    static ITimeKeeper& getInstance() {
        static MockTimeKeeper instance;
        return instance;
    }

    void update() override;
    static void setTime(unsigned long newTime);

    // Elimina i metodi di copia e assegnazione per evitare copie dell'istanza singleton
    MockTimeKeeper(const MockTimeKeeper&) = delete;  // TimeKeeper tk2 = tk1;  // NO
    void operator=(const MockTimeKeeper&) = delete; // tk2 = tk1; // NO
};






class Timer
{
  private:
    unsigned long oldTime;
    unsigned long timeDuration;
    bool startInterlock;
    ITimeKeeper& timeKeeper;
  public:
    Timer(unsigned long timeDuration);
  
    void active(bool start);
    bool isTimeElapsed();
    void setTime(unsigned long newTime);
    void reset();
};

class DigitalInput
{
  private:
    unsigned int pin;
    unsigned int value;
    unsigned int oldValue;
    unsigned int trigChanged;
    Timer* activationTimer;

  public:
  DigitalInput(unsigned int pin, unsigned long threshold);
 
    
    void update();
    bool isActive();
    bool isChanged();
};


class DigitalOutput
{
  private:
    unsigned int pin;
    unsigned int value;

  public:
    DigitalOutput(unsigned int pin);
  
    
    void update();
    void turnOn();
    void turnOff();
    bool isActive();

};



class AnalogInput
{
  private:
    unsigned int pin;
    float value;
    unsigned int mapValue;
    static const unsigned int maxFilterSize = 10;
    int array[maxFilterSize];
    unsigned int filterCount;
    float val_coef = 0;
    int currentIndex = 0;
    float filterValue(unsigned int inputValue);

  public:
    AnalogInput(unsigned int pin, unsigned int mapValue);
    void update();
    int getValue();
};


class AnalogOutput
{
  private:
    unsigned int pin;
    unsigned int value;
    unsigned int maxValue;

  public:
    AnalogOutput(unsigned int pin, unsigned int maxValue);
    
    
    void setValue(unsigned int value);
    int getValue();
    void update();
};


/*
class Screen
{
  private:
    LiquidCrystal_I2C lcd;
    bool lock;

  public:
    Screen(unsigned int address, unsigned int columns, unsigned int rows)
    {
      this->lcd = LiquidCrystal_I2C(address, columns, rows);
      this->lock = 0;
    }
    
    void clearScreen();
    void lock();
    void unlock();
    void print(String message, int row);
};


#endif



void clearScreen(Screen *screen){
  screen->lcd.clear();
  screen->lock = 0;
}

void print(Screen *screen, String message, int row, int lock)
{
  if (!lock)
  {
    screen->lock = false;
  }
  
  if (!screen->lock)
  {
    screen->lock = false;
    print(screen, message, row);
  }
 
  if (lock)
  {
    screen->lock = true;
  }
}

void print(Screen *screen, String message, int row)
{
  screen->lcd.setCursor(0, row);
  screen->lcd.print(message);

#ifdef DEBUG
  Serial.println(message);
  Serial.flush();
#endif
}

*/

#endif