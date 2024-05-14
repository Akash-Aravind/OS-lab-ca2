#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define NUM_CHAIRS 3
#define SIMULATION_STEPS 20

// States
#define SLEEPING 0
#define CUTTING 1
#define WAITING 2

// Barber and customer states
int barber_state = SLEEPING;
int waiting_customers = 0;
int total_customers = 0;

// Function prototypes
void customer_arrives();
void barber_cut_hair();
void simulate();

int main() {
    simulate();
    return 0;
}

void simulate() {
    for (int i = 0; i < SIMULATION_STEPS; i++) {
        // Randomly decide if a new customer arrives
        if (rand() % 2 == 0) {
            customer_arrives();
        }

        // Barber checks to cut hair
        barber_cut_hair();

        sleep(1); // Simulate time passing
    }

    printf("Simulation ended.\nTotal customers served: %d\nCustomers who left: %d\n",
           total_customers, (total_customers - waiting_customers));
}

void customer_arrives() {
    printf("A customer arrives.\n");

    if (waiting_customers < NUM_CHAIRS) {
        waiting_customers++;
        total_customers++;
        printf("Customer sits in waiting area. Waiting customers: %d\n", waiting_customers);

        if (barber_state == SLEEPING) {
            barber_state = CUTTING;
            printf("Barber wakes up to cut hair.\n");
        }
    } else {
        printf("No available chairs. Customer leaves.\n");
    }
}

void barber_cut_hair() {
    if (waiting_customers > 0 && barber_state == CUTTING) {
        printf("Barber is cutting hair.\n");
        waiting_customers--;
        printf("One customer served. Waiting customers: %d\n", waiting_customers);

        if (waiting_customers == 0) {
            barber_state = SLEEPING;
            printf("Barber goes to sleep.\n");
        }
    } else if (barber_state == SLEEPING) {
        printf("Barber is sleeping.\n");
    }
}
