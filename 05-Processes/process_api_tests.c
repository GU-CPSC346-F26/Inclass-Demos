#include "sys/types.h"
#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>

void child_lives_parent_terminates()
{
    if (fork() == 0) {
        /* Child */
        printf("Running Child, PID = %d\n", getpid());
        for(int x = 0; x < 5; x++){
            printf("%d, Child Process %d has parent %d\n", x, getpid(), getppid());
            sleep(1);
        }
    } else {
        sleep(1);
        printf("Terminating Parent, PID = %d\n", getpid());
        exit(0);
    }
}
void parent_wont_stop() {
    if (fork() == 0) {
        /* Child */
        printf("Terminating Child, PID = %d\n", getpid());
        exit(0);
    } else {
        printf("Running Parent, PID = %d\n", getpid());
        while (1)
            ; /* Infinite loop */
    }
}


int main() {
    int option = 1;
    switch(option){
        case 0:
            parent_wont_stop();
            break;
        case 1:
            child_lives_parent_terminates();
            break;
    }
    return 0;
}

