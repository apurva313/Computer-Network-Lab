#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999

// Struct for the edges of the graph
struct Edge {
    int u; // Start vertex of the edge
    int v; // End vertex of the edge
    int w; // Weight of the edge (u, v)
};

// Graph - it consists of edges
struct Graph {
    int V; // Total number of vertices in the graph
    int E; // Total number of edges in the graph
    struct Edge *edge; // Array of edges
};

void bellmanford(struct Graph *g, int source);
void display(int arr[], int size);

int main(void) {
    // Create graph
    struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
    g->V = 4; // Total vertices
    g->E = 5; // Total edges

    // Array of edges for graph
    g->edge = (struct Edge *)malloc(g->E * sizeof(struct Edge));

    // Adding the edges of the graph
    /*
    edge(u, v)
    where u = start vertex of the edge (u, v)
    v = end vertex of the edge (u, v)
    w is the weight of the edge (u, v)
    */

    // edge 0 --> 1
    g->edge[0].u = 0;
    g->edge[0].v = 1;
    g->edge[0].w = 5;

    // edge 0 --> 2
    g->edge[1].u = 0;
    g->edge[1].v = 2;
    g->edge[1].w = 4;

    // edge 1 --> 3
    g->edge[2].u = 1;
    g->edge[2].v = 3;
    g->edge[2].w = 3;

    // edge 2 --> 1
    g->edge[3].u = 2;
    g->edge[3].v = 1;
    g->edge[3].w = 6;

    // edge 3 --> 2
    g->edge[4].u = 3;
    g->edge[4].v = 2;
    g->edge[4].w = 2;

    bellmanford(g, 0); // 0 is the source vertex

    // Free allocated memory
    free(g->edge);
    free(g);

    return 0;
}

void bellmanford(struct Graph *g, int source) {
    int i, j, u, v, w;
    int tV = g->V; // Total vertices in the graph g
    int tE = g->E; // Total edges in the graph g
    int d[tV]; // Distance array
    int p[tV]; // Predecessor array

    // Step 1: Fill the distance array and predecessor array
    for (i = 0; i < tV; i++) {
        d[i] = INFINITY;
        p[i] = -1; // Using -1 to indicate no predecessor
    }

    // Mark the source vertex
    d[source] = 0;

    // Step 2: Relax edges |V| - 1 times
    for (i = 1; i <= tV - 1; i++) {
        for (j = 0; j < tE; j++) {
            u = g->edge[j].u;
            v = g->edge[j].v;
            w = g->edge[j].w;

            if (d[u] != INFINITY && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                p[v] = u;
            }
        }
    }

    // Step 3: Detect negative cycle
    for (i = 0; i < tE; i++) {
        u = g->edge[i].u;
        v = g->edge[i].v;
        w = g->edge[i].w;

        if (d[u] != INFINITY && d[v] > d[u] + w) {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    // No negative weight cycle found
    // Print the distance and predecessor array
    printf("Distance array: ");
    display(d, tV);
    printf("Predecessor array: ");
    display(p, tV);
}

void display(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
