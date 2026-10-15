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

void transfer_once(account_t *from, account_t *to, int amount, int tid) {
    printf("[T%d] acquiring %s\n", tid, from->name);
    usleep(1000); // Simulate work while holding first lock
    pthread_mutex_lock(&from->lock);
    printf("[T%d] acquiring %s\n", tid, to->name);
    pthread_mutex_lock(&to->lock);

    if (from->balance >= amount) {
        from->balance -= amount;
        to->balance   += amount;
    }

    pthread_mutex_unlock(&to->lock);
    pthread_mutex_unlock(&from->lock);
}

void *transfer_loop(void *arg) {
    transfer_args_t *a = (transfer_args_t *)arg;
    for (int i = 0; i < a->iters; i++) {
        transfer_once(a->from, a->to, a->amount, a->id);
        usleep(1000);
    }
    return NULL;
}

int main(void) {
    // initialize two account structs
    account_t A = { .name="A", .balance=1000, .lock=PTHREAD_MUTEX_INITIALIZER };
    account_t B = { .name="B", .balance=1000, .lock=PTHREAD_MUTEX_INITIALIZER };
    pthread_t t1, t2;

    // initialize two arg structs
    transfer_args_t a1 = { .from=&A, .to=&B, .amount=1, .iters=100, .id=1 };
    transfer_args_t a2 = { .from=&B, .to=&A, .amount=1, .iters=100, .id=2 };

    printf("Starting balances: A=%d, B=%d\n", A.balance, B.balance);

    pthread_create(&t1, NULL, transfer_loop, &a1);
    pthread_create(&t2, NULL, transfer_loop, &a2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Ending balances:  A=%d, B=%d\n", A.balance, B.balance);
    return 0;
}
