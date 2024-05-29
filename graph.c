#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_SCENARIOS; i++) {
        graph->head[i] = NULL;
    }
}

void addEdge(Graph* graph, int src, int dest) {
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->scenarioIndex = dest;
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->scenarioIndex = src;
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < MAX_SCENARIOS; i++) {
        GraphNode* temp = graph->head[i];
        printf("\n Scenario %d\n: ", i);
        while (temp) {
            printf("%d -> ", temp->scenarioIndex);
            temp = temp->next;
        }
        printf("\n");
    }
}
