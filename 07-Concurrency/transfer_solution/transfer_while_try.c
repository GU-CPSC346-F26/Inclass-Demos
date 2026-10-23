
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    const char *name;
    int balance;
    pthread_mutex_t lock;
} account_t;

typedef struct {
    account_t *from;
    account_t *to;
    int amount;
    int iters;
    int id;
} transfer_args_t;

static void transfer_once(account_t *from, account_t *to, int amount, int tid) {
    while (1){
        // printf("[T%d] trying lock %s\n", tid, from->name);
        pthread_mutex_lock(&from->lock);
        // printf("[T%d]   got   lock %s\n", tid, from->name);

    // Make the interleaving window bigger

        // printf("[T%d] trying lock %s\n", tid, to->name);
        if(!pthread_mutex_trylock(&to->lock)){
            break;
        }
        // printf("[T%d] unlock %s\n", tid, from->name);
        pthread_mutex_unlock(&from->lock);
        // usleep(100);
    }
    // printf("[T%d]   got   lock %s\n", tid, to->name);
    // Critical section: do the transfer
    if (from->balance >= amount) {
        from->balance -= amount;
        to->balance   += amount;
    }

    pthread_mutex_unlock(&to->lock);
    pthread_mutex_unlock(&from->lock);
}

static void *transfer_loop(void *arg) {
    transfer_args_t *a = (transfer_args_t *)arg;
    int count = 0;
    for (int i = 0; i < a->iters; i++) {
        transfer_once(a->from, a->to, a->amount, a->id);
        count++;
        // printf("COUNT = %d\n", count);
        // small pause to mix schedules
        usleep(1000);
    }
    return NULL;
}

int main(void) {
    account_t A = { .name="A", .balance=2000, .lock=PTHREAD_MUTEX_INITIALIZER };
    account_t B = { .name="B", .balance=1000, .lock=PTHREAD_MUTEX_INITIALIZER };

    pthread_t t1, t2;

    transfer_args_t a1 = { .from=&A, .to=&B, .amount=1, .iters=5, .id=1 };
    transfer_args_t a2 = { .from=&B, .to=&A, .amount=1, .iters=10, .id=2 };

    printf("Starting balances: A=%d, B=%d\n", A.balance, B.balance);

    pthread_create(&t1, NULL, transfer_loop, &a1);
    pthread_create(&t2, NULL, transfer_loop, &a2);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Ending balances:  A=%d, B=%d\n", A.balance, B.balance);
    return 0;
}
