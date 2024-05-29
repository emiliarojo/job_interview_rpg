#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h> // Include standard library for memory allocation

typedef struct Node {
    int scenarioIndex;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void enqueue(Queue* queue, int scenarioIndex);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
void initializeQueue(Queue* queue);

#endif
