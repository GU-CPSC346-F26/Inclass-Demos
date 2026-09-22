#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * Worksheet 2 - Wait and Exec
 *
 * Compile:
 *     gcc worksheet2_demo.c -o worksheet2_demo
 *
 * Run:
 *     ./worksheet2_demo 1
 *     ./worksheet2_demo 2
 *     ...
 *     ./worksheet2_demo 5
 */


void ws_1(void) {
	int value = 5;
	pid_t x;

	if ((x = fork()) == 0) {
		/* child process */
		value += 15;

		/* The child has no children of its own, so this returns immediately. */
		wait(NULL);

		printf("CHILD: value = %d\n", value);
		return;
	}
	else if (x > 0) {
		/* parent process */
		wait(NULL);

		printf("PARENT: value = %d\n", value);
		return;
	}

	perror("fork");
}


void ws_2(void) {
	for (int i = 0; i < 3; i++) {
		if (fork() == 0) {
			printf("Child %d: PID=%d\n", i, getpid());
			exit(10 + i);
		}
	}

	int status;
	pid_t x;

	while ((x = wait(&status)) > 0) {
		printf("Parent reaped PID=%d with status=%d\n",
			x, WEXITSTATUS(status));
	}
}



void ws_3(void) {
	if (fork() == 0) {
		printf("Child running with parent PID=%d\n", getppid());

		sleep(5);

		printf("Child done. Parent PID=%d\n", getppid());
	}
	else {
		printf("Parent exiting early.\n");
		exit(0);
	}
}


void ws_4(void) {
	printf("Before exec\n");

	execlp("ls", "ls", "-l", NULL);

	/*
	 * exec only returns if it fails.
	 * Therefore this normally never prints.
	 */
	printf("After exec\n");
}


void ws_5(void) {
	printf("Start\n");

	if (fork() == 0) {
		char *args[] = {"echo", "Child running", NULL};

		execv("/bin/echo", args);

		/*
		 * This only runs if execv() fails.
		 */
		printf("Echo Complete\n");
	}
	else {
		printf("Parent before wait\n");

		wait(NULL);

		printf("Parent after wait\n");
	}
}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <worksheet number 1-5>\n", argv[0]);
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

		case 5:
			ws_5();
			break;

		default:
			printf("Invalid worksheet number. Choose 1-5.\n");
			return 1;
	}

	return 0;
}
