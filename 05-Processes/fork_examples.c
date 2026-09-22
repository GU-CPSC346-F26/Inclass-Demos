#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void child_parent_flip() {
    pid_t pid;
    pid_t ParentPid = getppid();

    if ((pid = fork()) == 0) {
        ParentPid  = getppid();
        printf("Child: fork-%d, Parent-%d, getpid-%d\n", pid, ParentPid, getpid());
        return;
    }
    sleep(1);
    printf("Parent:fork-%d, Parent-%d, getpid-%d\n", pid, ParentPid, getpid());

}


void nested_forks_parent(){
    printf("L0\n");
    if(fork()!= 0){
        printf("L1\n");
        if(fork() != 0){
            printf("L2\n");
        }
    }
    printf("Bye\n");
}

void nested_forks_children(){
    printf("L0\n");
    if(fork()==0){
        printf("L1\n");
        if(fork() == 0){
            printf("L2\n");
        }
    }
    printf("Bye\n");
}

void wait_in_order(){
    pid_t pid[3];
    int i;
    for (i = 0; i < 3; i++){
        if((pid[i]=fork())==0){
            printf("Child %d (%d) is running\n",i, getpid());
            if(i == 0){
                sleep(4);
            }
            
            execlp("echo", "echo", "child", NULL);
        }
    }
    for(i = 0; i<3; i++){
        printf("looop %d\n", i);
        pid_t w = waitpid(pid[i], NULL, 0);
        printf("Reaped child with pid = %d\n", w);
    }
}
void donothing(int * a){
    *a = 10;
    return;
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

int main( ) {

    // child_parent_flip();
    // nested_forks_children();
    nested_forks_parent();
    // wait_in_order();

    // if (fork()==0){ 
        
    //     printf("a\n");

    // }
    // else{
    //     int x = 5;
    //     donothing(&x);
    //     sleep(2);
    //     printf("b\n");

    //     wait(NULL);

    // } 
    // sleep(2);
    // printf("c\n"); 
    // exit(0); 

}