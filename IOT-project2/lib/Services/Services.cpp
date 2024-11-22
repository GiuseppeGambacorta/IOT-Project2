#include "Services.h"


/*---- SERVICE LOCATOR ----*/
// allocation of the static variable
ITimeKeeper* ServiceLocator::timeKeeper = &TimeKeeper::getInstance();
IInputKeeper* ServiceLocator::inputKeeper = &RealInputKeeper::getInstance();


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





/*---- INPUT KEEPER ABSTRACT CLASS ----*/

IInputKeeper::IInputKeeper() {}

bool IInputKeeper::getDigitalPinState(unsigned int pin) {

    if (pin >= NUM_DIGITAL_PINS) {
        return false;
    }
    return digitalPins[pin];
}

unsigned int IInputKeeper::getAnalogPinValue(unsigned int pin) {

    if (pin >= NUM_ANALOG_INPUTS) {
        return 0;
    }
    return analogPins[pin];
}



/*---- INPUT KEEPER WITH DIGITALREAD() AND ANALOGREAD() ----*/

RealInputKeeper::RealInputKeeper() : IInputKeeper() {}

IInputKeeper& RealInputKeeper::getInstance() {
    static RealInputKeeper instance;
    return instance;
}

void RealInputKeeper::update() {
    for (int i = 0; i < NUM_DIGITAL_PINS; i++) {
        digitalPins[i] = digitalRead(i);
    }

    for (int i = 0; i < NUM_ANALOG_INPUTS; i++) {
        analogPins[i] = analogRead(i);
    }
}
