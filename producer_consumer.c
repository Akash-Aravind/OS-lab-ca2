#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_SLOTS 5
int mutex_sem = 1;
int empty_sem = NUM_SLOTS;
int full_sem = 0;
int index = -1;
int buffer[NUM_SLOTS];

void wait(int *semaphore) {
    while (*semaphore <= 0) {
        usleep(1000);
    }
    *semaphore -= 1;
}

void signall(int *semaphore) {
    *semaphore += 1;
}

void producer() {
    wait(&mutex_sem);
    if (full_sem == NUM_SLOTS) {
        printf("Buffer is full. Producer waiting...\n");
        signall(&mutex_sem);
        return;
    }
    index++;
    full_sem++;
    empty_sem--;
    buffer[index] = 1; // Add item to the buffer
    printf("Producer produced item %d\n", index);
    signall(&mutex_sem);
}

void consumer() {
    wait(&mutex_sem);
    if (empty_sem == NUM_SLOTS) {
        printf("Buffer is empty. Consumer waiting...\n");
        signall(&mutex_sem);
        return;
    }
    int item = buffer[index];
    index--;
    full_sem--;
    empty_sem++;
    printf("Consumer consumed item %d\n", item);
    signall(&mutex_sem);
}

int main() {
    pthread_t producers[NUM_SLOTS];
    pthread_t consumers[NUM_SLOTS];
    int i;

    for (i = 0; i < NUM_SLOTS; i++) {
        pthread_create(&producers[i], NULL, (void *)producer, NULL);
        pthread_create(&consumers[i], NULL, (void *)consumer, NULL);
    }

    for (i = 0; i < NUM_SLOTS; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
