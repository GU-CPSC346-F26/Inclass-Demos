#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void ws_1(){
    pid_t fork_output;
    pid_t ParentPid = getpid();

    if ((fork_output = fork()) == 0) {
        printf("Child: fork-%d, Parent-%d, getpid-%d\n", fork_output, ParentPid, getpid());
        return;
    }

    printf("Parent:fork-%d, Parent-%d, getpid-%d\n", fork_output, ParentPid, getpid());

    return; 
}

void ws_2(){
    pid_t x = fork();
    if(x>0){
        fork();
        printf("Hello!\n");
    }
    printf("Hello!\n");
}

void ws_3(){
    fork();
    sleep(1);
    printf("Hello!\n");
    fork();
    printf("Goodbye!\n");
}



void ws_4(){
    int x = 1;
    if (fork()==0){
        printf("p1: x = %d\n", ++x);
       
    }
    // wait(NULL);
    sleep(1);
    printf("p2: x = %d\n", --x);
}

void prob7() {
    //pstree -sap <child_id>
    if (fork() == 0) {
        printf("Child PID=%d initial parent PID=%d\n", getpid(), getppid());
        sleep(20);
        printf("Child PID=%d after sleep parent PID=%d\n", getpid(), getppid());
        _exit(0);
    } else {
        printf("Parent exiting early.\n");
        sleep(10);
        _exit(0);
    }
}

void prob8(){
    if(fork()==0){
        printf("A\n");
        if(fork()==0){
            sleep(3);
            printf("B\n");
        }
    }
    else{
        wait(NULL);
        printf("C\n");
    }
    printf("D\n");
    return;
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: %s <worksheet number 1-4>\n", argv[0]);
		return 1;
	}

	int ws_num = atoi(argv[1]);

	switch (ws_num) {
		case 1:
			ws_1();
			break;
		case 2:
			ws_2();
			break;
		case 3:
			ws_3();
			break;
		case 4:
			ws_4();
			break;
		default:
			printf("Invalid worksheet number. Choose 1-4.\n");
			return 1;
	}

	return 0;
}
