#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
int chopstick[NUM_PHILOSOPHERS] = {1, 1, 1, 1, 1}; // 1 represents available, 0 represents taken

void wait(int *chopstick) {
    while (*chopstick == 0) {
        // Wait until chopstick is available
        usleep(1000); // Sleep for a short time to avoid busy waiting
    }
    *chopstick = 0; // Mark chopstick as taken
}

void signall(int *chopstick) {
    *chopstick = 1; // Mark chopstick as available
}

void *philosopher(void *arg) {
    int id = *((int *)arg);
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);

        // Pick up chopsticks
        wait(&chopstick[id]);
        wait(&chopstick[(id + 1) % NUM_PHILOSOPHERS]);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        usleep(1000000); // Simulate eating time

        // Put down chopsticks
        signall(&chopstick[id]);
        signall(&chopstick[(id + 1) % NUM_PHILOSOPHERS]);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    int i;

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads (this part is never reached in this example)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

