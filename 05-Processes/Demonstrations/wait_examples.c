#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void zombie() {
    if (fork() == 0) {
        /* Child */
        printf("Terminating Child, PID = %d\n", getpid());
        execv("/bin/ls", NULL);
        printf("HELLO!");   // Child exits normally
    } else {
        /* Parent */
        printf("Running Parent, PID = %d\n", getpid());
        // while (1)
        //     ;  // Infinite loop: parent never terminates or reaps child
    }
}

void orphan() {
    //pstree -sap <child_id>
    if (fork() == 0) {
        printf("Child PID=%d initial parent PID=%d\n", getpid(), getppid());
        sleep(10);
        printf("Child PID=%d after sleep parent PID=%d\n", getpid(), getppid());
        exit(0);
    } else {
        sleep(3);
        printf("Parent exiting early.\n");
        exit(0);
    }
}


void fork11(int N) {
    pid_t pid[N];
    int i;
    int child_status;

    // Create N child processes
    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            // Child process
            
            // if (i%2 == 0){
            //     sleep(1);
            // }
            exit(100 + i);
        }
    }

    // Parent waits for each child in reverse order
    for (i = N - 1; i >= 0; i--) {
        pid_t wpid = waitpid(pid[i], &child_status, 0);

        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n",
                   wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminated abnormally\n", wpid);
        }
    }
}

int main( ) {
    // orphan();
    zombie();
    // fork11(10);
    return 0;

}
