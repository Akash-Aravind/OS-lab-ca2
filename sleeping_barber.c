#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_SEATS 5  // Number of waiting room seats

int barberReady = 0;
int accessSeats = 1;
int customerReady = 0;
int freeSeats = NUM_SEATS;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void wait(int* semaphore) {
    while (*semaphore == 0) {
        usleep(1000);  // Sleep for 1 millisecond.
    }
    *semaphore = 0;
}

void signall(int* semaphore) {
    *semaphore = 1;
}

void* barberProcess(void* arg) {
    while (1) {
        wait(&customerReady);  // Sleep if no customers.
        wait(&accessSeats);    // Ensure mutually exclusive access to seats.
        freeSeats++;           // One waiting room seat becomes free.
        signall(&barberReady); // The barber is ready to cut hair.
        signall(&accessSeats); // Release the seat access lock.
        printf("Barber is cutting hair\n");
        sleep(1);              // Simulate hair cutting time.
    }
}

void* customerProcess(void* arg) {
    while (1) {
        wait(&accessSeats);  // Ensure mutually exclusive access to seats.
        if (freeSeats > 0) {
            freeSeats--;                          // Sit in the waiting room.
            signall(&customerReady);              // Notify the barber.
            signall(&accessSeats);                // Release the seat access lock.
            wait(&barberReady);                   // Wait for the barber to be ready.
            printf("Customer is getting a haircut\n");
            sleep(1);                             // Simulate hair cutting time.
        } else {
            // No free seats, leave without getting a haircut.
            signall(&accessSeats);                // Release the seat access lock.
            printf("Customer leaves without haircut\n");
            sleep(1);                             // Simulate time before a new customer arrives.
        }
    }
}

int main() {
    pthread_t barberThread;
    pthread_t customerThreads[NUM_SEATS];

    // Create barber thread
    pthread_create(&barberThread, NULL, barberProcess, NULL);

    // Create customer threads
    int i;
    for ( i = 0; i < NUM_SEATS; i++) {
        pthread_create(&customerThreads[i], NULL, customerProcess, NULL);
        sleep(1);  // Simulate time delay between new customers.
    }

    // Join threads
    pthread_join(barberThread, NULL);
    for ( i = 0; i < NUM_SEATS; i++) {
        pthread_join(customerThreads[i], NULL);
    }

    return 0;
}

