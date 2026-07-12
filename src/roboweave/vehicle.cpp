#include "vehicle.h"
#include <Arduino.h>

// Constructor: stores pointers to previously created motors
Vehicle::Vehicle(Motor *leftMotor, Motor *rightMotor)
    : leftMotor(leftMotor), rightMotor(rightMotor)
{
}

// Initializes the hardware of all the vehicle's motors
void Vehicle::init()
{
    leftMotor->init();
    rightMotor->init();
}

void Vehicle::forward(int speed)
{
    leftMotor->forward(speed);
    rightMotor->forward(speed);
}

void Vehicle::backward(int speed)
{
    leftMotor->backward(speed);
    rightMotor->backward(speed);
}

void Vehicle::stop()
{
    leftMotor->stop();
    rightMotor->stop();
}

// Pivot turn left: left motor backward, right motor forward
void Vehicle::turnLeft(int speed)
{
    leftMotor->backward(speed);
    rightMotor->forward(speed);
}

// Pivot turn right: left motor forward, right motor backward
void Vehicle::turnRight(int speed)
{
    leftMotor->forward(speed);
    rightMotor->backward(speed);
}

// Smooth turn left: the left (inner) motor slows down by a percentage,
// the right (outer) motor stays at full speed
void Vehicle::turnLeftSmooth(int speed, int turnPercent)
{
    turnPercent = constrain(turnPercent, 0, 100);
    int innerSpeed = speed * (100 - turnPercent) / 100;

    leftMotor->forward(innerSpeed);
    rightMotor->forward(speed);
}

// Smooth turn right: the right (inner) motor slows down by a percentage,
// the left (outer) motor stays at full speed
void Vehicle::turnRightSmooth(int speed, int turnPercent)
{
    turnPercent = constrain(turnPercent, 0, 100);
    int innerSpeed = speed * (100 - turnPercent) / 100;

    leftMotor->forward(speed);
    rightMotor->forward(innerSpeed);
}
