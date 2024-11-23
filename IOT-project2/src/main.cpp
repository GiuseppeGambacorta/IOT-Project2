#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "Motor/Motor.h"

// Definizione degli stati
enum MotorState {
    INIT,
    MOVE_TO_90,
    MOVE_TO_MINUS_90,
    WAIT
};

Motor motor(9, 90, 90, -90);
MotorState currentState = INIT; // Stato iniziale
Timer wait = Timer(1000);
void setup() {
    Serial.begin(9600);
    motor.init();
    motor.setPosition(0);
    delay(2000);
}

void loop() {
    ServiceLocator::getTimeKeeperInstance().update();

    wait.active(currentState == WAIT);
        switch (currentState) {
            case INIT:
                motor.setPosition(0);
                if (motor.isInPosition()) {
                    currentState = MOVE_TO_90;
                }
                break;

            case MOVE_TO_90:
                motor.setPosition(90);
                if (motor.isInPosition()) {
                    currentState = MOVE_TO_MINUS_90;
                }
                break;

            case MOVE_TO_MINUS_90:
                motor.setPosition(-90);
                if (motor.isInPosition()) {
                    currentState = INIT;
                }
                break;

              case WAIT:
                if (wait.isTimeElapsed()) {
                    currentState = INIT;
                }
                
                break;

        }





      

    
     
    
}