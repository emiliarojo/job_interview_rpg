#include "graph.h"
#include <stdio.h>

void initializeGraph(Graph *g) {
    for (int i = 0; i < MAX_SCENARIOS; i++) {
        for (int j = 0; j < MAX_SCENARIOS; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int src, int dest) {
    g->adjMatrix[src][dest] = 1;
    g->adjMatrix[dest][src] = 1;
}

void printGraph(Graph *g) {
    for (int i = 0; i < MAX_SCENARIOS; i++) {
        for (int j = 0; j < MAX_SCENARIOS; j++) {
            printf("%d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}
