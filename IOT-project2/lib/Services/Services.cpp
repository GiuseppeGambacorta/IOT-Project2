#include "Services.h"


/*---- TIME KEEPER ----*/

TimeKeeper::TimeKeeper() : ITimeKeeper() {}

void TimeKeeper::update() {
    this->currentTime = millis();
}



/*---- MOCK TIME KEEPER ----*/
void MockTimeKeeper::update() {
    ;
}

void MockTimeKeeper::setTime(unsigned long newTime) {
    this->currentTime = newTime;
}
