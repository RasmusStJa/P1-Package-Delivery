//
// Created by Rasmus on 11-12-2024.
//

#ifndef A_STAR_H
#define A_STAR_H
#define NUM_MAIN_NODES 15
#define NUM_INTERMEDIATE_NODES 5
//#define INF INT_MAX
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

double a_star(Node nodes[], int num_nodes, Edge edges[], int num_edges, int start, int goal);

void print_a_star_results(const double main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES]);

void print_nodes(unsigned int num_nodes, const Node nodes[]);

double euclidean_heuristic(Node a, Node b);

void populate_nodes(Node nodes[], unsigned int num_nodes);

void populate_edges(Edge edges[], Node nodes[], unsigned int num_nodes);

void shortest_distance_main_nodes(Node nodes[], Edge edges[], double *main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES]);

#endif //A_STAR_H
