#include "Services.h"


/*---- SERVICE LOCATOR ----*/
// allocation of the static variable
ITimeKeeper* ServiceLocator::timeKeeper = &TimeKeeper::getInstance();


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

MockTimeKeeper::MockTimeKeeper() : ITimeKeeper() {}

ITimeKeeper& MockTimeKeeper::getInstance() {
    static MockTimeKeeper instance;
    return instance;
}

void MockTimeKeeper::update() {
    ;
}

void MockTimeKeeper::setTime(unsigned long newTime) {
    this->currentTime = newTime;
}
