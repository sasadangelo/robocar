#include "motor.h"
#include <Arduino.h>

// Constructor with member initialization
Motor::Motor(int in1, int in2, int ena)
{
    pinIN1 = in1;
    pinIN2 = in2;
    pinENA = ena;
}

// Pin initialization
void Motor::init()
{
    pinMode(pinIN1, OUTPUT);
    pinMode(pinIN2, OUTPUT);
    pinMode(pinENA, OUTPUT);
}

// Forward
void Motor::forward(int speed)
{
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, LOW);
    analogWrite(pinENA, speed);
}

// Backward
void Motor::backward(int speed)
{
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, HIGH);
    analogWrite(pinENA, speed);
}

// Stop
void Motor::stop()
{
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, LOW);
    analogWrite(pinENA, 0);
}