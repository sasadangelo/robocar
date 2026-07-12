#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
private:
    int pinIN1;
    int pinIN2;
    int pinENA;

public:
    // Constructor
    Motor(int in1, int in2, int ena);

    // Public methods
    void init();
    void forward(int speed);
    void backward(int speed);
    void stop();
};

#endif // MOTOR_H