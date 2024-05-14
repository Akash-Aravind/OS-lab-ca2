#include <stdio.h>
#include <stdbool.h>

// Number of processes
#define P 5

// Number of resources
#define R 3

// Function prototypes
void calculate_need(int need[P][R], int max[P][R], int allot[P][R]);
bool is_safe(int processes[], int avail[], int max[][R], int allot[][R]);
void print_safe_sequence(int safe_seq[]);

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {0, 3, 0};

    // Maximum R that can be allocated to processes
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources allocated to processes
    int allot[P][R] = {
        {0, 1, 10},
        {12, 0, 0},
        {3, 10, 2},
        {12, 1, 1},
        {0, 0, 12}
    };

    // Check system is in a safe state or not
    if (is_safe(processes, avail, max, allot)) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}

// Calculate the need matrix
void calculate_need(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Check system is in a safe state or not
bool is_safe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculate_need(need, max, allot);

    // Mark all processes as not finished
    bool finish[P] = {0};
    // To store safe sequence
    int safe_seq[P];
    // Copy the available resources
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            // Check if process p can be allocated
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    safe_seq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }

    print_safe_sequence(safe_seq);
    return true; // System is in a safe state
}

// Print the safe sequence
void print_safe_sequence(int safe_seq[]) {
    printf("Safe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safe_seq[i]);
    }
    printf("\n");
}
