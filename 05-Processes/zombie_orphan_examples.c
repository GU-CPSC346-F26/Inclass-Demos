#include "sys/types.h"
#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>

void child_lives_parent_terminates(){
    // child is an orphan
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
    // child is a zombie
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


int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: %s <0 for orphan example, 1 for zombie example\n", argv[0]);
		return 1;
	}

	int num = atoi(argv[1]);

	switch (num) {
		case 0:
			child_lives_parent_terminates();
			break;
		case 1:
			parent_wont_stop();
			break;
	}

	return 0;
}

