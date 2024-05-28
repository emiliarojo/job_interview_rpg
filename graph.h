#ifndef GRAPH_H
#define GRAPH_H

#define MAX_SCENARIOS 4

typedef struct {
    int adjMatrix[MAX_SCENARIOS][MAX_SCENARIOS];
} Graph;

void initializeGraph(Graph *g);
void addEdge(Graph *g, int src, int dest);
void printGraph(Graph *g);

#endif
