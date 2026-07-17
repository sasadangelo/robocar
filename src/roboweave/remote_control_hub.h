#ifndef REMOTE_CONTROL_HUB_H
#define REMOTE_CONTROL_HUB_H

#include "remote_control.h"

// Composite RemoteControl: aggregates several concrete remotes (IR, Bluetooth,
// ...) behind the single RemoteControl interface, so the main program can
// treat them as one
class RemoteControlHub : public RemoteControl
{
private:
    static const int MAX_REMOTES = 4;
    RemoteControl *remotes[MAX_REMOTES];
    int remoteCount;

public:
    RemoteControlHub();

    // Registers a new remote hardware (IR, Bluetooth, radio...) with the hub
    void registerRemote(RemoteControl *remote);

    // Initializes all registered remotes at once
    void init() override;

    // Polls every registered remote and returns the first non-CMD_NONE command
    Command getCommand() override;
};

#endif // REMOTE_CONTROL_HUB_H
