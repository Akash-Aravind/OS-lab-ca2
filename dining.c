#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Number of philosophers
#define NUM_PHILOSOPHERS 5

// States of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

// Philosopher states
int state[NUM_PHILOSOPHERS];

// Forks availability
int forks[NUM_PHILOSOPHERS];

// Function prototypes
void think(int philosopher_id);
void pick_up_forks(int philosopher_id);
void put_down_forks(int philosopher_id);
void eat(int philosopher_id);
void test(int philosopher_id);

// Helper functions for more realistic simulation
int can_pick_up_forks(int philosopher_id);
void philosopher_action(int philosopher_id);

int main() {
    // Initialize philosophers to THINKING state and forks to available
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        state[i] = THINKING;
        forks[i] = 1;
    }

    // Simulate the dining philosophers
    for (int i = 0; i < 20; i++) { // Simulate 20 cycles
        for (int j = 0; j < NUM_PHILOSOPHERS; j++) {
            philosopher_action(j);
        }
        sleep(1); // Simulate time passing
    }

    return 0;
}

void philosopher_action(int philosopher_id) {
    switch (state[philosopher_id]) {
        case THINKING:
            think(philosopher_id);
            break;
        case HUNGRY:
            pick_up_forks(philosopher_id);
            break;
        case EATING:
            eat(philosopher_id);
            put_down_forks(philosopher_id);
            break;
    }
}

void think(int philosopher_id) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    state[philosopher_id] = HUNGRY;
}

void pick_up_forks(int philosopher_id) {
    if (can_pick_up_forks(philosopher_id)) {
        int left_fork = philosopher_id;
        int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

        forks[left_fork] = 0;
        forks[right_fork] = 0;
        state[philosopher_id] = EATING;
        printf("Philosopher %d picked up forks %d and %d.\n", philosopher_id, left_fork, right_fork);
    }
}

void put_down_forks(int philosopher_id) {
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    forks[left_fork] = 1;
    forks[right_fork] = 1;
    state[philosopher_id] = THINKING;
    printf("Philosopher %d put down forks %d and %d.\n", philosopher_id, left_fork, right_fork);
}

void eat(int philosopher_id) {
    printf("Philosopher %d is eating.\n", philosopher_id);
    state[philosopher_id] = THINKING;
}

int can_pick_up_forks(int philosopher_id) {
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;
    return forks[left_fork] == 1 && forks[right_fork] == 1;
}
