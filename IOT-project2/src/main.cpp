#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "Motor.h"

// Definizione degli stati
enum MotorState {
    INIT,
    MOVE_TO_90,
    MOVE_TO_MINUS_90,
    MOVE_TO_0
};

Motor motor(9, 90, 90, -90);
Timer moveMotor(50); // Timer per gestire il tempo tra le transizioni di stato
bool start;
MotorState currentState = INIT; // Stato iniziale

void setup() {
    Serial.begin(9600);
    motor.init();
    motor.setPosition(0);
    delay(2000);
}

void loop() {
    ServiceLocator::getTimeKeeperInstance().update();
    moveMotor.active(start);

 
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
                    Serial.println("state: " + String(currentState));
                    Serial.println("Position: " + String(motor.getPosition()));
                    currentState = MOVE_TO_MINUS_90;
                }
                break;

            case MOVE_TO_MINUS_90:
                motor.setPosition(-90);
                if (motor.isInPosition()) {
                     Serial.println("state: " + String(currentState));
                    Serial.println("Position: " + String(motor.getPosition()));
                    currentState = INIT;
                }
                break;

        }
    

      start = !moveMotor.isTimeElapsed();


      

    
     
    
}