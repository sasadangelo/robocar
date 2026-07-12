#ifndef VEHICLE_H
#define VEHICLE_H

#include <motor.h>

class Vehicle
{
private:
    Motor *leftMotor; // Motor pointers to avoid copies in memory
    Motor *rightMotor;

public:
    // The constructor accepts pointers to previously created motors
    Vehicle(Motor *leftMotor, Motor *rightMotor);

    // Initializes the hardware of all the vehicle's motors
    void init();

    void forward(int speed);
    void backward(int speed);
    void stop();

    // Pivot turn on the spot: one motor forward, the other backward at the same speed
    void turnLeft(int speed);
    void turnRight(int speed);

    // Smooth turn while moving: the inner motor slows down by a percentage
    // (turnPercent, 0-100), the outer motor stays at full speed
    void turnLeftSmooth(int speed, int turnPercent);
    void turnRightSmooth(int speed, int turnPercent);
};

#endif
