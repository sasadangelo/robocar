#include "elegoo_robot_car.h"

// Left motor pins (IN1, IN2, ENA) and right motor pins (IN1, IN2, ENA)
// wired as on the Elegoo Smart Robot Car V3.0 shield
ElegooRobotCar::ElegooRobotCar()
    : Vehicle(&leftMotor, &rightMotor),
      leftMotor(7, 8, 5),
      rightMotor(11, 9, 6),
      version(3)
{
}

int ElegooRobotCar::getVersion() const
{
    return version;
}
