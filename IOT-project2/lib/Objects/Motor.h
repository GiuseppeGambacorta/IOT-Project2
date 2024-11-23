
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
  Servo motor;

public:
  Motor(unsigned int pin, unsigned int offsetPosition, int upperLimit, int lowerLimit);
  void init();
  void setPosition(int value);
  int getPosition();
  bool isMoving();
  bool isAtUpperLimit();
  bool isAtLowerLimit();
};



#endif // MOTOR_H