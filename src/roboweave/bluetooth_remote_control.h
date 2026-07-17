#ifndef BLUETOOTH_REMOTE_CONTROL_H
#define BLUETOOTH_REMOTE_CONTROL_H

#include "remote_control.h"

// Bluetooth implementation of RemoteControl, based on serial communication
class BluetoothRemoteControl : public RemoteControl
{
private:
    long baudRate;

public:
    // Configures the Bluetooth serial port with the given baud rate (e.g. 9600)
    BluetoothRemoteControl(long baudRate = 9600);

    void init() override;
    Command getCommand() override;
};

#endif // BLUETOOTH_REMOTE_CONTROL_H
