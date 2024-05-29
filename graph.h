#ifndef GRAPH_H
#define GRAPH_H

#define MAX_SCENARIOS 6

typedef struct GraphNode {
    int scenarioIndex;
    struct GraphNode* next;
} GraphNode;

typedef struct {
    GraphNode* head[MAX_SCENARIOS];
} Graph;

void initializeGraph(Graph* graph);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);

#endif
