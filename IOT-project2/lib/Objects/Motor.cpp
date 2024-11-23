#include "motor.h"



Motor::Motor(unsigned int pin, unsigned int offsetPosition, int upperLimit, int lowerLimit)
    : pin(pin), offsetPosition(offsetPosition), upperLimit(upperLimit), lowerLimit(lowerLimit)
{
}


void Motor::setPosition(int value)
{
    if (value >= lowerLimit && value <= upperLimit)
    {
        motor.write(value+offsetPosition);
    }
}


int Motor::getPosition()
{
    return motor.read() - offsetPosition;
}


bool Motor::isMoving()
{
    return motor.attached();
}

bool Motor::isAtUpperLimit()
{
    return this->Motor::getPosition() >= upperLimit;
}

bool Motor::isAtLowerLimit()
{
    return this->getPosition() <= lowerLimit;
}


void Motor::init()
{
    motor.attach(pin);
}