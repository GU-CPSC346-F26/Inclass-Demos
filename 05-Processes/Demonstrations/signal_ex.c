#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int caught = 0;
// Custom signal handler
void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT)\n", sig);
    if (caught > 0){
        printf("Exiting");
        exit(0);
    }
    kill(getpid(), SIGCONT);

    caught++;
}

int main() {
    // Register the handler for SIGINT
    // if (signal(SIGINT, handle_sigint) == SIG_ERR) {
    //     perror("signal");
    //     return 1;
    // }

    printf("Running... press Ctrl+C to trigger SIGINT\n");

    // Keep the program running until a signal is received
    pause();
    while (1) {
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}
