#include <Arduino.h>
#include <elegoo_robot_car.h>
#include <ir_remote_control.h>

ElegooRobotCar car;

// Concrete hardware: an IR receiver on pin 12
IRRemoteControl irRemote(12);

// The rest of the program only talks to the RemoteControl interface, so
// swapping the IR remote for e.g. a Bluetooth one only means changing this
// line (a reference, not a pointer: no dynamic allocation, no null checks)
RemoteControl &remote = irRemote;

void setup()
{
  // Initialize the motors hardware
  car.init();

  // Initialize the remote control hardware
  remote.init();
}

void loop()
{
  Command cmd = remote.getCommand();

  switch (cmd)
  {
  case CMD_FORWARD:
    car.forward(180);
    break;
  case CMD_BACKWARD:
    car.backward(180);
    break;
  case CMD_LEFT:
    car.turnLeft(160);
    break;
  case CMD_RIGHT:
    car.turnRight(160);
    break;
  case CMD_STOP:
    car.stop();
    break;
  case CMD_NONE:
  default:
    break;
  }
}
