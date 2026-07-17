#include "remote_control_hub.h"

RemoteControlHub::RemoteControlHub()
{
    remoteCount = 0;
    for (int i = 0; i < MAX_REMOTES; i++)
    {
        remotes[i] = nullptr;
    }
}

void RemoteControlHub::registerRemote(RemoteControl *remote)
{
    if (remoteCount < MAX_REMOTES)
    {
        remotes[remoteCount] = remote;
        remoteCount++;
    }
}

void RemoteControlHub::init()
{
    // Pure polymorphism: initializes each hardware remote without knowing its type
    for (int i = 0; i < remoteCount; i++)
    {
        remotes[i]->init();
    }
}

Command RemoteControlHub::getCommand()
{
    // Polls every registered remote in turn
    for (int i = 0; i < remoteCount; i++)
    {
        Command cmd = remotes[i]->getCommand();

        // As soon as one of them returns a real command, return it immediately
        if (cmd != CMD_NONE)
        {
            return cmd;
        }
    }

    // Nobody received anything
    return CMD_NONE;
}
