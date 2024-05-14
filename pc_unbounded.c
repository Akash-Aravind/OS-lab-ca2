#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Node structure for the linked list (unbounded buffer)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
void produce_item(int producer_id);
void consume_item(int consumer_id);
void simulate();
void enqueue(int item);
int dequeue();

// Global variables
Node* head = NULL;
Node* tail = NULL;
int item_count = 0;

int main() {
    simulate();
    return 0;
}

void simulate() {
    for (int i = 0; i < 20; i++) { // Simulate 20 steps
        // Simulate producers
        for (int j = 0; j < 2; j++) { // Assume 2 producers
            produce_item(j);
        }

        // Simulate consumers
        for (int k = 0; k < 2; k++) { // Assume 2 consumers
            consume_item(k);
        }

        sleep(1); // Simulate time passing
    }
    printf("Simulation ended.\n");
}

void produce_item(int producer_id) {
    int item = rand() % 100; // Produce a random item
    enqueue(item);
    printf("Producer %d produced item %d. Total items in buffer: %d\n", producer_id, item, item_count);
}

void consume_item(int consumer_id) {
    if (item_count > 0) {
        int item = dequeue();
        printf("Consumer %d consumed item %d. Total items in buffer: %d\n", consumer_id, item, item_count);
    } else {
        printf("Consumer %d found buffer empty, skipping consumption.\n", consumer_id);
    }
}

void enqueue(int item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    new_node->data = item;
    new_node->next = NULL;

    if (tail) {
        tail->next = new_node;
    } else {
        head = new_node;
    }
    tail = new_node;
    item_count++;
}

int dequeue() {
    if (!head) {
        fprintf(stderr, "Buffer underflow error\n");
        exit(1);
    }
    Node* temp = head;
    int item = head->data;
    head = head->next;
    if (!head) {
        tail = NULL;
    }
    free(temp);
    item_count--;
    return item;
}
