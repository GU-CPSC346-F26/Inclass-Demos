
#include "sys/types.h"
#include "stdio.h"
#include "unistd.h"


int main() {
	int pid;
	pid=fork();
	if(pid>0){
		fork();
		printf("Hello!\n");
	}	
	printf("Hello!\n");
	return 0;
}

