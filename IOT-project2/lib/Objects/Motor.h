
#include "ArduinoStandardLibrary.h"
#include "Servo.h"

#ifndef MOTOR_H
#define MOTOR_H


class Motor
{
private:
  unsigned int pin;
  unsigned int offsetPosition;
  int upperLimit;
  int lowerLimit;
  bool initialized = false;
  int lastCommandPosition = 0;
  Servo motor;
  Timer checkPositionTimer = Timer(450);

public:
  Motor(unsigned int pin, unsigned int offsetPosition, int upperLimit, int lowerLimit);
  void init();
  void setPosition(int value);
  int getPosition();
  bool isInPosition();
  bool isMoving();
  bool isAtUpperLimit();
  bool isAtLowerLimit();
};



#endif // MOTOR_H