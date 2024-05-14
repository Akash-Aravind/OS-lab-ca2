#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

void wait(int *semaphore) {
    while (*semaphore <= 0) {
        usleep(1000);
    }
    *semaphore -= 1;
}

void signall(int *semaphore) {
    *semaphore += 1;
}

void produce(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
}

int consume() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    return item;
}

void *producer(void *arg) {
    int item = 0;
    while (1) {
        printf("Producer is producing item %d...\n", item);
        pthread_mutex_lock(&buffer_mutex);
        if (count < BUFFER_SIZE) {
            produce(item);
            printf("Producer produced item %d.\n", item);
            item++;
        }
        pthread_mutex_unlock(&buffer_mutex);
        usleep(1000000); // Producer sleep
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&buffer_mutex);
        if (count > 0) {
            item = consume();
            printf("Consumer consumed item %d.\n", item);
            signall(&count); // Signal buffer space available
        }
        pthread_mutex_unlock(&buffer_mutex);
        usleep(2000000); // Consumer sleep
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create producer thread
    pthread_create(&producer_thread, NULL, producer, NULL);

    // Create consumer thread
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads (this part is never reached in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}

