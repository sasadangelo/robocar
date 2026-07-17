#include "ir_remote_control.h"
#include <Arduino.h>
#include <IRremote.hpp>

// Constructor with member initialization
IRRemoteControl::IRRemoteControl(int pin)
{
    this->pin = pin;
}

// Starts the IR receiver on the configured pin
void IRRemoteControl::init()
{
    IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);
}

// Decodes the NEC command and maps it to a universal command. Matching
// on the NEC command byte (instead of decodedRawData) is stable across
// IRremote library versions, and keeps working on button-repeat frames
// since decodedIRData.command is retained across repeats.
Command IRRemoteControl::getCommand()
{
    if (!IrReceiver.decode())
    {
        return CMD_NONE;
    }

    uint16_t command = IrReceiver.decodedIRData.command;
    IrReceiver.resume();

    switch (command)
    {
    case 0x46:
        return CMD_FORWARD;
    case 0x15:
        return CMD_BACKWARD;
    case 0x44:
        return CMD_LEFT;
    case 0x43:
        return CMD_RIGHT;
    case 0x40:
        return CMD_STOP;
    default:
        return CMD_NONE;
    }
}
