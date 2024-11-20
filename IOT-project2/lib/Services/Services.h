
#include <Arduino.h>

#ifndef SERVICES_H
#define SERVICES_H


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
    void setTime(unsigned long newTime);

    // Elimina i metodi di copia e assegnazione per evitare copie dell'istanza singleton
    MockTimeKeeper(const MockTimeKeeper&) = delete;  // TimeKeeper tk2 = tk1;  // NO
    void operator=(const MockTimeKeeper&) = delete; // tk2 = tk1; // NO
};




class ServiceFactory {

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