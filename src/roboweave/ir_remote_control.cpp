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

// Decodes the raw IR code and maps it to a universal command.
// Two codes per command are handled because some remotes send a
// different raw code depending on the NEC protocol variant.
Command IRRemoteControl::getCommand()
{
    if (!IrReceiver.decode())
    {
        return CMD_NONE;
    }

    unsigned long rawData = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume();

    switch (rawData)
    {
    case 0xFF629D:
    case 0x1FE48B7:
        return CMD_FORWARD;
    case 0xFFA857:
    case 0x1FE906F:
        return CMD_BACKWARD;
    case 0xFF22DD:
    case 0x1FE10EF:
        return CMD_LEFT;
    case 0xFFC23D:
    case 0x1FE58A7:
        return CMD_RIGHT;
    case 0xFF02FD:
    case 0x1FEA05F:
        return CMD_STOP;
    default:
        return CMD_NONE;
    }
}
