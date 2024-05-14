#include <stdio.h>
#include <stdlib.h>

// Shared variables
int read_count = 0;
int shared_data = 0; // The data that readers read and writers modify

// Function prototypes
void reader(int reader_id);
void writer(int writer_id);

// State variables to simulate concurrency
int current_reader_id = 0;
int current_writer_id = 0;

// Simulation function to manage state
void simulate_concurrent_operations();

// Reader function
void reader(int reader_id) {
    read_count++;
    if (read_count == 1) {
        // Simulate acquiring write lock (exclusive access)
    }

    // Critical section (reading)
    printf("Reader %d is reading shared data: %d\n", reader_id, shared_data);

    read_count--;
    if (read_count == 0) {
        // Simulate releasing write lock (exclusive access)
    }
}

// Writer function
void writer(int writer_id) {
    // Simulate acquiring write lock (exclusive access)

    // Critical section (writing)
    shared_data++;
    printf("Writer %d is writing shared data: %d\n", writer_id, shared_data);

    // Simulate releasing write lock (exclusive access)
}

int main() {
    // Initialize state variables
    current_reader_id = 1;
    current_writer_id = 1;

    // Simulate concurrent operations
    simulate_concurrent_operations();

    return 0;
}

void simulate_concurrent_operations() {
    for (int i = 0; i < 10; i++) {
        // Simulate interleaved execution of readers and writers
        if (i % 2 == 0) {
            reader(current_reader_id++);
        } else {
            writer(current_writer_id++);
        }
    }
}
