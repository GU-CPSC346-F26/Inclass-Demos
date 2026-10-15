#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int max;
int balance = 0; // shared global variable

void *mythread(void *arg)
{
    char *letter = (char *)arg;
    int i; // stack (private per thread)
    printf("%s: begin [addr of i: %p] [balance = %d at %p]\n", letter, &i, balance, &balance);
    printf("%s: Thread id: %lu, Process id: %d\n", letter, (unsigned long) pthread_self(), getpid());
    
    for (i = 0; i < max; i++) {
        balance = balance + 1;
    }
    printf("%s: done\n", letter);

    return NULL;
}

int main(int argc, char *argv[])
{
    
    if (argc != 2) {
        fprintf(stderr, "usage: main-first <loopcount>\n");
        exit(1);
    }
    max = atoi(argv[1]);

    pthread_t p1, p2;
    printf("main: begin [balance = %d] [%p]\n", balance, &balance);

    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("main: done\n [balance: %d]\n [should : %d]\n",
           balance, max * 2);
    return 0;
}
