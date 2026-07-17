#include <Arduino.h>
#include <elegoo_robot_car.h>
#include <ir_remote_control.h>
#include <bluetooth_remote_control.h>
#include <remote_control_hub.h>

ElegooRobotCar car;

// Central hub: aggregates every remote control hardware behind the single
// RemoteControl interface, so the rest of the program never branches on
// which concrete remote produced the command
RemoteControlHub remoteHub;

void setup()
{
  // Initialize the motors hardware
  car.init();

  // Register the concrete remotes with the hub. Add or remove one here
  // without touching loop().
  remoteHub.registerRemote(new IRRemoteControl(12));
  remoteHub.registerRemote(new BluetoothRemoteControl(9600));

  // Initialize all registered remote control hardware
  remoteHub.init();
}

void loop()
{
  Command cmd = remoteHub.getCommand();

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
