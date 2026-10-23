#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    const char *name;
    int balance;
    int lock_order;
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
    // Determine global lock ordering
    account_t *first = from;
    account_t *second = to;

    if (from->lock_order > to->lock_order) {
        first = to;
        second = from;
    }

    // Always acquire locks in the same order
    pthread_mutex_lock(&first->lock);
    pthread_mutex_lock(&second->lock);

    // Critical section: do the transfer
    if (from->balance >= amount) {
        from->balance -= amount;
        to->balance += amount;
    }

    // Release locks in reverse order
    pthread_mutex_unlock(&second->lock);
    pthread_mutex_unlock(&first->lock);
}

static void *transfer_loop(void *arg) {
    transfer_args_t *a = (transfer_args_t *)arg;

    for (int i = 0; i < a->iters; i++) {
        transfer_once(a->from, a->to, a->amount, a->id);
        usleep(1000);
    }

    return NULL;
}

int main(void) {
    account_t A = {
        .name = "A",
        .balance = 2000,
        .lock_order = 0,
        .lock = PTHREAD_MUTEX_INITIALIZER
    };

    account_t B = {
        .name = "B",
        .balance = 1000,
        .lock_order = 1,
        .lock = PTHREAD_MUTEX_INITIALIZER
    };

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