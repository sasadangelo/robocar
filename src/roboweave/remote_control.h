#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

// Universal commands recognized by the system, independent of the
// specific remote control hardware (IR, Bluetooth, ...)
enum Command
{
    CMD_NONE,
    CMD_FORWARD,
    CMD_BACKWARD,
    CMD_LEFT,
    CMD_RIGHT,
    CMD_STOP
};

// Pure interface for remote controls: the main program only depends on
// this contract, never on the specific hardware (IR, Bluetooth, ...)
class RemoteControl
{
public:
    virtual ~RemoteControl() {}

    // Initializes the specific hardware
    virtual void init() = 0;

    // Checks for a new command and returns it, hiding the hardware-specific
    // encoding (e.g. an IR raw code or a Bluetooth character); returns
    // CMD_NONE when no command is available
    virtual Command getCommand() = 0;
};

#endif // REMOTE_CONTROL_H
