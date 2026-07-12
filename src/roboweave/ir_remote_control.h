#ifndef IR_REMOTE_CONTROL_H
#define IR_REMOTE_CONTROL_H

#include "remote_control.h"

// IR receiver implementation of RemoteControl, based on the IRremote library
class IRRemoteControl : public RemoteControl
{
private:
    int pin;

public:
    // The IR receiver module is connected to the given digital pin
    IRRemoteControl(int pin);

    void init() override;
    Command getCommand() override;
};

#endif // IR_REMOTE_CONTROL_H
