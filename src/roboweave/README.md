# roboweave

roboweave is RoboCar's library for managing the vehicle's mechanical parts: motors and movement. It exposes a simple API for driving the Elegoo Smart Robot Car V3.0, keeping the control logic (in the main program) separate from the hardware details.

## Architecture

The library is organized in three layers:

- **`Motor`** ([motor.h](motor.h) / [motor.cpp](motor.cpp)) — controls a single DC motor via the IN1, IN2 and ENA pins of an H-bridge driver. Exposes `init()`, `forward(speed)`, `backward(speed)` and `stop()`.
- **`Vehicle`** ([vehicle.h](vehicle.h) / [vehicle.cpp](vehicle.cpp)) — combines a left and a right motor to manage the vehicle's movement: forward/backward drive, pivot turns on the spot (`turnLeft`/`turnRight`), and smooth turns while moving (`turnLeftSmooth`/`turnRightSmooth`), where the inner motor slows down by a percentage while the outer motor keeps full speed.
- **`ElegooRobotCar`** ([elegoo_robot_car.h](elegoo_robot_car.h) / [elegoo_robot_car.cpp](elegoo_robot_car.cpp)) — specializes `Vehicle` with the specific wiring of the Elegoo Smart Robot Car V3.0 shield (left motor on pins 7/8/5, right motor on pins 11/9/6).

```
ElegooRobotCar  (board-specific wiring)
      │
      ▼
   Vehicle       (movement logic: forward, backward, turns)
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

## Adding support for a new vehicle

To reuse `Motor` and `Vehicle` with a different car model, create a new class that extends `Vehicle` and configures the motor pins for that specific wiring, following the same pattern as `ElegooRobotCar`.
