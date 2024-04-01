#include "sig_prog.h"

void handler(int signum) {
    if (signum == SIGUSR1)
        printf("sigusr1 detected!\n");
}