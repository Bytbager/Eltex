#include "sig_prog.h"

int main(int argc, char **argv) {
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    int signum;

    if (argc != 2) {
        fprintf(stderr, "Usage:\n"
        "%s with-sigwait - run this program with sigwait (while (1) {sigwait(SIGUSR1)})\n"
        "%s no-sigwait - run this program without sigwait (while (1) {})\n"
        , argv[0], argv[0]);
        return -1;
    }

    act.sa_handler = handler;
    if (sigemptyset(&act.sa_mask) == -1)
        errExit("sigemptyset error!\n");
    if (sigaction(SIGUSR1, &act, NULL) == -1)
        errExit("sigaction error!\n");

    if (strcmp(argv[1], "with-sigwait") == 0) {
        while (1) {
            if (sigwait(&act.sa_mask, &signum) != 0)
                errExit("sigwait error!\n");
        }
    } else if (strcmp(argv[1], "no-sigwait") == 0) {
        while (1) {}
    } else {
        fprintf(stderr, "Usage:"
        "%s with-sigwait - run this program with while (1) {sigwait(SIGUSR1)}\n"
        "%s no-sigwait - run this program without sigwait (while (1) {})\n"
        , argv[0], argv[0]);
        return -1;
    }

    return 0;
}