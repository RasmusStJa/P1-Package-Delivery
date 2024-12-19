#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define NUM_MAIN_NODES 15
#define NUM_INTERMEDIATE_NODES 5
#define INF INT_MAX
#define GRID_WIDTH 30
#define GRID_HEIGHT 30

typedef struct {
   int id;
   double x, y;
} Node;

typedef struct {
   int start, end;
   double cost;
} Edge;

//SHA: Function to calculate the Euclidean distance
double euclidean_heuristic(const Node a, const Node b) {
   return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//SHA: A* Algorithm
double a_star(Node nodes[], const int num_nodes, Edge edges[], const int num_edges, int start, int goal) {
   //SHA: OPEN and CLOSED sets
   int *open_set = calloc(num_nodes, sizeof(int));  //SHA: 1 if in OPEN, 0 otherwise
   int *closed_set = calloc(num_nodes, sizeof(int)); //SHA: 1 if in CLOSED, 0 otherwise
   //SHA: g(node) and f(node) scores
   double *g_score = malloc(num_nodes * sizeof(double));
   double *f_score = malloc(num_nodes * sizeof(double));
   int *came_from = malloc(num_nodes * sizeof(int));

   for (unsigned int i = 0; i < num_nodes; i++) {
       g_score[i] = INF;
       f_score[i] = INF;
       came_from[i] = -1;
   }

   //SHA: Initialization
   g_score[start] = 0;
   f_score[start] = euclidean_heuristic(nodes[start], nodes[goal]);
   open_set[start] = 1;

    int while_counter = 0;
    while (while_counter < INF - 1000) {
        while_counter++;
        //SHA: Find node in OPEN with lowest f(node)
        int current = -1;
        double min_f_score = INF;
        for (unsigned int i = 0; i < num_nodes; i++) {
            if (open_set[i] && f_score[i] < min_f_score) {
                min_f_score = f_score[i];
                current = i;
            }
        }


        //SHA: If OPEN is empty, return error (no solution)
        if (current == -1) {
            free(g_score);
            free(f_score);
            free(open_set);
            free(closed_set);
            free(came_from);
            return INF; //SHA: No solution
        }


        //SHA: If current is the goal, reconstruct path
        if (current == goal) {
            const double result = g_score[goal];
            free(g_score);
            free(f_score);
            free(open_set);
            free(closed_set);
            free(came_from);
            return result;
        }

        //SHA: Move current from OPEN to CLOSED
        open_set[current] = 0;
        closed_set[current] = 1;

        //SHA: For each neighbor of current
        for (unsigned int i = 0; i < num_edges; i++) {
            if (edges[i].start == current) {
                const int neighbor = edges[i].end;

                //SHA: Skip if neighbor is in CLOSED
                if (closed_set[neighbor]) continue;

                const double tentative_g_score = g_score[current] + edges[i].cost;

                if (!open_set[neighbor]) {
                    //SHA: Add neighbor to OPEN
                    open_set[neighbor] = 1;
                } else if (tentative_g_score >= g_score[neighbor]) {
                    //SHA: Skip if current path is not better
                    continue;
                }

               //SHA: Record path and scores
               came_from[neighbor] = current;
               g_score[neighbor] = tentative_g_score;
               f_score[neighbor] = g_score[neighbor] + euclidean_heuristic(nodes[neighbor], nodes[goal]);
            }
        }
    }
}

void print_nodes(const unsigned int num_nodes, const Node nodes[]) {
    printf("Nodes (ID, X, Y):\n");
    for (unsigned int i = 0; i < num_nodes; i++) {
        printf("Node ID: %d, X: %.2f, Y: %.2f\n",
            nodes[i].id,
            nodes[i].x,
            nodes[i].y
            );
    }

    printf("\nMain Nodes:\n");
    for (unsigned int i = 0; i < NUM_MAIN_NODES; i++) {
        const int main_node_id = i * NUM_INTERMEDIATE_NODES; //SHA: First intermediate node for each main node
        printf("Main Node %d -> Node ID: %d, X: %.2f, Y: %.2f\n",
            i,
            nodes[main_node_id].id, nodes[main_node_id].x, nodes[main_node_id].y
            );
    }

    printf("\nIntermediate Nodes:\n");
    for (unsigned int i = 0; i < NUM_MAIN_NODES; i++) {
        for (unsigned int j = 0; j < NUM_INTERMEDIATE_NODES; j++) {
            const int intermediate_node_id = i * NUM_INTERMEDIATE_NODES + j;
            printf("Intermediate Node (%d-%d) -> Node ID: %d, X: %.2f, Y: %.2f\n",
                i, j,
                nodes[intermediate_node_id].id,
                nodes[intermediate_node_id].x,
                nodes[intermediate_node_id].y
                );
        }
    }
}

void printMatrix(const double matrix[NUM_MAIN_NODES][NUM_MAIN_NODES]) {
    //RAS: print every node in the same line
    printf("     "); //RAS: formatting
    for (unsigned int i = 0; i < NUM_MAIN_NODES; i++) {
        printf("%d     ", i);
        //RAS: if less than 2 characters, add a space
        if (i < 10) { printf(" "); }
    }
    printf("\n");
    for (unsigned int y = 0; y < NUM_MAIN_NODES; y++) { //RAS: column
        for (unsigned int x = 0; x < NUM_MAIN_NODES; x++) { //RAS: row
            //RAS: at start of each line print index
            if (x == 0) {
                //RAS: compensate for the extra space
                if (y < 10) { printf(" "); }
                printf("%d  ", y);
            }
            if (matrix[y][x] < 10) { printf(" "); }
            printf("%.2f  ", matrix[x][y]);
        }
        printf("\n");
    }
}

void print_a_star_results(const double main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES]) {
    printf("\nShortest Paths Between Main Nodes:\n");
    printMatrix(main_node_distances);
    /*
    for (int i = 0; i < NUM_MAIN_NODES; i++) {
        for (int j = 0; j < NUM_MAIN_NODES; j++) {
            //RAS: Skip because a node's distance to itself will always be 0
            if (i == j) { continue; }
            printf("Distance from Main Node %d to Main Node %d: %.2f\n",
                i, j,
                main_node_distances[i][j]
                );
        }
    }*/
}

void populate_nodes(Node nodes[], const unsigned int num_nodes) {
    for (unsigned int i = 0; i < num_nodes; i++) {
        nodes[i].id = i;
        nodes[i].x = rand() % GRID_WIDTH;
        nodes[i].y = rand() % GRID_HEIGHT;
    }
}

void populate_edges(Edge edges[], Node nodes[], const unsigned int num_nodes) {
    //RAS: edge_count is basically 1 + 2 + 3 + ... + n (a triangular number)
    //RAS: this can then be calculated as n*(n+1)/2
    unsigned int edge_count = 0;
    for (unsigned int i = 0; i < num_nodes; i++) {
        for (unsigned int j = i + 1; j < num_nodes; j++, edge_count++) {
            edges[edge_count].start = i;
            edges[edge_count].end = j;
            edges[edge_count].cost = euclidean_heuristic(nodes[i], nodes[j]);
        }
    }
}