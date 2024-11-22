#include <unity.h>
#include "ArduinoStandardLibrary.h"


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
    DigitalInput button(0,0);

    TEST_ASSERT_FALSE(button.isActive());
    TEST_ASSERT_FALSE(button.isChanged());

    InputKeeper.setDigitalPinState(0, true);
    button.update();
    TEST_ASSERT_TRUE(button.isActive());
    TEST_ASSERT_TRUE(button.isChanged());

    button.update();
    TEST_ASSERT_TRUE(button.isActive());
    TEST_ASSERT_FALSE(button.isChanged());

    InputKeeper.setDigitalPinState(0, false);
    button.update();

    TEST_ASSERT_FALSE(button.isActive());
    TEST_ASSERT_TRUE(button.isChanged());
 
}



void setup() {
    UNITY_BEGIN(); // Inizia il testing
    RUN_TEST(test_digitalRead_noDelay);
    UNITY_END(); // Termina il testing
}

void loop() {
    // Vuoto
}