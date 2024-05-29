#include "queue.h"
#include <stdlib.h>

void enqueue(Queue* queue, int scenarioIndex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->scenarioIndex = scenarioIndex;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }
    int scenarioIndex = queue->front->scenarioIndex;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return scenarioIndex;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void initializeQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}
