#include "Services.h"



/*---- TIME KEEPER ABSTRACT CLASS ----*/

ITimeKeeper::ITimeKeeper() : currentTime(0) {}

unsigned long ITimeKeeper::getCurrentTime() {
    return this->currentTime;
}



/*---- TIME KEEPER WITH MILLIS() ----*/

TimeKeeper::TimeKeeper() : ITimeKeeper() {}

ITimeKeeper& TimeKeeper::getInstance() {
    static TimeKeeper instance;
    return instance;
}

void TimeKeeper::update() {
    this->currentTime = millis();
}



/*---- MOCK TIME KEEPER ----*/

TimeKeeper::TimeKeeper() : ITimeKeeper() {}

ITimeKeeper& TimeKeeper::getInstance() {
    static TimeKeeper instance;
    return instance;
}

void MockTimeKeeper::update() {
    ;
}

void MockTimeKeeper::setTime(unsigned long newTime) {
    this->currentTime = newTime;
}
