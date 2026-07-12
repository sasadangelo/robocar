#ifndef ELEGOO_ROBOT_CAR_H
#define ELEGOO_ROBOT_CAR_H

#include <vehicle.h>

class ElegooRobotCar : public Vehicle
{
private:
    Motor leftMotor;
    Motor rightMotor;
    int version;

public:
    // Elegoo Smart Robot Car V3.0: motors are wired to the shield's fixed pins
    ElegooRobotCar();

    int getVersion() const;
};

#endif
