# RoboCar

RoboCar is the control software for the **Elegoo Smart Robot Car V3.0**, written in C++ with the Arduino framework and managed with [PlatformIO](https://platformio.org/).

The project is organized into two parts:

- **[roboweave](src/roboweave/README.md)** — the library that manages the vehicle's mechanical parts (motors, wheels, movement), exposing a simple API independent of the specific car model.
- **robocar** — the main program ([src/robocar/main.cpp](src/robocar/main.cpp)) that uses roboweave to drive the Elegoo Robot Car: it initializes the hardware and implements the control logic (movement sequences, behaviors, etc.).

## Project structure

```
robocar/
├── platformio.ini          # PlatformIO configuration (board, framework, build flags)
├── src/
│   ├── robocar/
│   │   └── main.cpp        # Main control program
│   └── roboweave/
│       ├── motor.h/.cpp        # Single motor control (IN1/IN2/ENA pins)
│       ├── vehicle.h/.cpp      # Vehicle movement (forward, backward, turns)
│       ├── elegoo_robot_car.h/.cpp # Board-specific configuration for the Elegoo Robot Car V3.0
│       ├── remote_control.h    # RemoteControl interface and universal Command enum
│       └── ir_remote_control.h/.cpp # IR remote implementation of RemoteControl
└── test/                    # Project tests
```

## Requirements

- [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html) or [PlatformIO IDE](https://platformio.org/platformio-ide) (VS Code extension)
- Elegoo Smart Robot Car V3.0 (Arduino Uno based)

## Build and upload

```bash
# Build the firmware
pio run

# Upload the firmware to the board (Arduino Uno connected via USB)
pio run --target upload

# Open the serial monitor
pio device monitor
```

## License

This project is licensed under the [MIT License](LICENSE).
