#include "bluetooth_remote_control.h"
#include <Arduino.h>

// Constructor with member initialization
BluetoothRemoteControl::BluetoothRemoteControl(long baudRate)
{
    this->baudRate = baudRate;
}

// Starts the hardware serial port used by the Bluetooth module
void BluetoothRemoteControl::init()
{
    Serial.begin(baudRate);
}

// Decodes the character received over Bluetooth and maps it to the universal command
Command BluetoothRemoteControl::getCommand()
{
    // No data in the serial buffer, so no command
    if (Serial.available() <= 0)
    {
        return CMD_NONE;
    }

    // Reads the single character sent by the smartphone app
    char serialChar = Serial.read();

    switch (serialChar)
    {
    case 'F': // Forward
        return CMD_FORWARD;
    case 'B': // Backward
        return CMD_BACKWARD;
    case 'L': // Left
        return CMD_LEFT;
    case 'R': // Right
        return CMD_RIGHT;
    case 'S': // Stop
        return CMD_STOP;
    default:
        return CMD_NONE;
    }
}
