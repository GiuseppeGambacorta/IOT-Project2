#include <unity.h>
#include "ArduinoStandardLibrary.h"

#define MAX_VALUE 100
#define ANALOG_PIN A0

// execute before each test
void setUp(void) {
    ServiceLocator::setInputKeeperInstance(MockInputKeeper::getInstance());
    ServiceLocator::setTimeKeeperInstance(MockTimeKeeper::getInstance());
}


// execute after each test
void tearDown(void) {
}

void test_digitalRead_noDelay(void) {
    MockInputKeeper& InputKeeper = (MockInputKeeper&) ServiceLocator::getInputKeeperInstance();
    AnalogInput potentiometer(ANALOG_PIN,MAX_VALUE);

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());
    
    InputKeeper.setAnalogPinValue(ANALOG_PIN, 0);
    potentiometer.update();
    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());

    InputKeeper.setAnalogPinValue(ANALOG_PIN, 1023);
    potentiometer.update();
    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());

 
}



void setup() {
    UNITY_BEGIN(); 
    RUN_TEST(test_digitalRead_noDelay);
    UNITY_END(); 
}

void loop() {
}