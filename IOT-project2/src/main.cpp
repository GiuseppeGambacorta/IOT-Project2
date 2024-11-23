#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "Components/Door/api/Door.h"

// Definizione degli stati
enum MotorState {
    INIT,
    MOVE_TO_90,
    MOVE_TO_MINUS_90,
    WAIT
};

Door door(9);
MotorState currentState = INIT; // Stato iniziale
Timer wait = Timer(1000);
void setup() {
    Serial.begin(9600);
    door.init();
    delay(2000);
}

void loop() {
    ServiceLocator::getTimeKeeperInstance().update();

    wait.active(currentState == WAIT);
        switch (currentState) {
            case INIT:
                door.close();
                if (door.isClosed()) {
                    currentState = MOVE_TO_90;
                }
                break;

            case MOVE_TO_90:
                door.open();
                if (door.isOpened()) {
                    currentState = MOVE_TO_MINUS_90;
                }
                break;

            case MOVE_TO_MINUS_90:
                door.empty();
                if (door.isInEmptyPosition()) {
                    currentState = INIT;
                }
                break;

              case WAIT:
                if (wait.isTimeElapsed()) {
                    currentState = INIT;
                }
                
                break;

        }

        Serial.println(currentState);





      

    
     
    
}