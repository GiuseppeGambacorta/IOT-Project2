#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
#include "scheduler/api/Scheduler.h"

Scheduler scheduler;

void setup() {
    Serial.begin(9600);
    delay(2000);
  // conto del tempo ottimale per i task
  scheduler.init(10); //inserire tempo ricavato opportunamente
}

void loop() {
  scheduler.schedule();
}

