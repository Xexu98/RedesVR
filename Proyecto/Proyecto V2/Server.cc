#include <string>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "GameServer.h"

int main(int argc, char **argv)
{
    sigset_t waitset;
    int sig;

    GameServer gameServer(argv[1], argv[2]);

    gameServer.serverThread();

    sigemptyset(&waitset);
    sigaddset(&waitset, SIGQUIT);

    sigwait(&waitset, &sig);

    return 0;
}