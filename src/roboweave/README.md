# roboweave

roboweave is RoboCar's library for managing the vehicle's mechanical parts (motors and movement) and its remote controls. It exposes a simple API for driving the Elegoo Smart Robot Car V3.0 and for receiving driving commands, keeping the control logic (in the main program) separate from the hardware details.

## Architecture

The library is organized in two independent hierarchies: one for the vehicle, one for the remote control.

- **`Motor`** ([motor.h](motor.h) / [motor.cpp](motor.cpp)) — controls a single DC motor via the IN1, IN2 and ENA pins of an H-bridge driver. Exposes `init()`, `forward(speed)`, `backward(speed)` and `stop()`.
- **`Vehicle`** ([vehicle.h](vehicle.h) / [vehicle.cpp](vehicle.cpp)) — combines a left and a right motor to manage the vehicle's movement: forward/backward drive, pivot turns on the spot (`turnLeft`/`turnRight`), and smooth turns while moving (`turnLeftSmooth`/`turnRightSmooth`), where the inner motor slows down by a percentage while the outer motor keeps full speed.
- **`ElegooRobotCar`** ([elegoo_robot_car.h](elegoo_robot_car.h) / [elegoo_robot_car.cpp](elegoo_robot_car.cpp)) — specializes `Vehicle` with the specific wiring of the Elegoo Smart Robot Car V3.0 shield (left motor on pins 7/8/5, right motor on pins 11/9/6).
- **`RemoteControl`** ([remote_control.h](remote_control.h)) — pure interface for remote controls: declares `init()` and `getCommand()`, the latter returning a universal `Command` (`CMD_FORWARD`, `CMD_BACKWARD`, `CMD_LEFT`, `CMD_RIGHT`, `CMD_STOP`, `CMD_NONE`). The main program depends only on this interface, never on the specific remote hardware.
- **`IRRemoteControl`** ([ir_remote_control.h](ir_remote_control.h) / [ir_remote_control.cpp](ir_remote_control.cpp)) — implements `RemoteControl` with an IR receiver module, using the [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) library to decode the raw NEC codes of a typical IR remote into universal commands.

```
ElegooRobotCar  (board-specific wiring)        RemoteControl        (universal command interface)
      │                                               │
      ▼                                               ▼
   Vehicle       (movement logic)              IRRemoteControl      (IR receiver, IRremote library)
      │
      ▼
    Motor         (single motor control via IN1/IN2/ENA pins)
```

## Main API

### Motor

| Method | Description |
|---|---|
| `Motor(in1, in2, ena)` | Constructor: motor control pins |
| `init()` | Configures the pins as outputs |
| `forward(speed)` | Drive forward at `speed` (0-255) |
| `backward(speed)` | Drive backward at `speed` (0-255) |
| `stop()` | Stops the motor |

### Vehicle

| Method | Description |
|---|---|
| `init()` | Initializes the hardware of both motors |
| `forward(speed)` / `backward(speed)` | Straight drive forward/backward |
| `stop()` | Stops the vehicle |
| `turnLeft(speed)` / `turnRight(speed)` | Pivot turn on the spot |
| `turnLeftSmooth(speed, turnPercent)` / `turnRightSmooth(speed, turnPercent)` | Smooth turn while moving: the inner motor slows down by `turnPercent` (0-100) |

### ElegooRobotCar

Extends `Vehicle` with the Elegoo Smart Robot Car V3.0 wiring, ready to use out of the box:

```cpp
#include <elegoo_robot_car.h>

ElegooRobotCar car;

void setup() {
    car.init();
}

void loop() {
    car.forward(150);
    delay(2000);
    car.stop();
}
```

### RemoteControl / IRRemoteControl

| Method | Description |
|---|---|
| `IRRemoteControl(pin)` | Constructor: digital pin the IR receiver is connected to |
| `init()` | Starts the IR receiver on the configured pin |
| `getCommand()` | Returns the decoded `Command`, or `CMD_NONE` if nothing was received |

```cpp
#include <elegoo_robot_car.h>
#include <ir_remote_control.h>

ElegooRobotCar car;
IRRemoteControl irRemote(12);
RemoteControl &remote = irRemote; // the rest of the code only depends on the interface

void setup() {
    car.init();
    remote.init();
}

void loop() {
    switch (remote.getCommand()) {
        case CMD_FORWARD:  car.forward(180);  break;
        case CMD_BACKWARD: car.backward(180); break;
        case CMD_LEFT:      car.turnLeft(160);  break;
        case CMD_RIGHT:     car.turnRight(160); break;
        case CMD_STOP:      car.stop();         break;
        default: break;
    }
}
```

## Adding support for a new vehicle

To reuse `Motor` and `Vehicle` with a different car model, create a new class that extends `Vehicle` and configures the motor pins for that specific wiring, following the same pattern as `ElegooRobotCar`.

## Adding support for a new remote control

To support a new type of remote (e.g. Bluetooth), create a new class that implements `RemoteControl` and translates its own hardware protocol into the universal `Command` values, following the same pattern as `IRRemoteControl`. The main program does not need any change beyond swapping which concrete class the `RemoteControl&` reference is bound to.
