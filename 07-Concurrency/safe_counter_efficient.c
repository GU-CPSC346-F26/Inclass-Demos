#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int max;
int balance = 0; 
pthread_mutex_t balance_lock = PTHREAD_MUTEX_INITIALIZER;
int threshold = 10000;

void *mythread(void *arg)
{
    char *letter = (char *)arg;
    int i; // stack (private per thread)
    printf("%s: begin [addr of i: %p] [balance = %d at %p]\n",
           letter, &i, balance, &balance);
    printf("%s: Thread id: %lu, Process id: %d\n", letter,(unsigned long) pthread_self(), getpid());
    
    int local = 0;
    for (i = 0; i < max; i++) {
        local++;
        if (local == threshold){
            pthread_mutex_lock(&balance_lock);
            balance += local;
            pthread_mutex_unlock(&balance_lock);
            local = 0;
        }
    }
    pthread_mutex_lock(&balance_lock);
    balance += local;
    pthread_mutex_unlock(&balance_lock);
    printf("%s: done\n", letter);

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: main-first <loopcount> <threshold\n");
        exit(1);
    }
    max = atoi(argv[1]);
    threshold = atoi(argv[2]);

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
