#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "held-karp.h"
#include "a-star.h"

int main() {
    printf("A-star:\n");

    srand(time(NULL)); //SHA: Seed the random number generator with the current time
    //TODO: Convert most (if not all) the following lines of code to functions

    //SHA: Define the intermediate graph
    const unsigned int num_nodes = NUM_INTERMEDIATE_NODES * NUM_MAIN_NODES;
    Node nodes[num_nodes];
    Edge edges[num_nodes * num_nodes];

    //SHA: Populate nodes with random coordinates
    populate_nodes(nodes, num_nodes);

    print_nodes(num_nodes, nodes);

    //SHA: Populate edges with costs
    populate_edges(edges, nodes, num_nodes);

    //SHA: Calculate the shortest path between main nodes
    const unsigned int edge_count = num_nodes * (num_nodes + 1) / 2; //RAS: look at line 157-158 in a-star.c
    double main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES];
    for (unsigned int i = 0; i < NUM_MAIN_NODES; i++) {
        for (unsigned int j = i + 1; j < NUM_MAIN_NODES; j++) {
            const int start = i * NUM_INTERMEDIATE_NODES;
            const int goal = j * NUM_INTERMEDIATE_NODES + NUM_INTERMEDIATE_NODES - 1;
            main_node_distances[i][j] = a_star(nodes, num_nodes, edges, edge_count, start, goal);
            main_node_distances[j][i] = main_node_distances[i][j]; //SHA: Symmetric
        }
    }

    //SHA: Print results
    printf("\nShortest Paths Between Main Nodes:\n");
    for (unsigned int i = 0; i < NUM_MAIN_NODES; i++) {
        for (unsigned int j = 0; j < NUM_MAIN_NODES; j++) {
            printf("Distance from Main Node %d to Main Node %d: %.2f\n", i, j, main_node_distances[i][j]);
        }
    }

    //SHA: Print results & calculate the shortest path between main nodes
    //print_a_star_results(shortest_distance_main_nodes(nodes, edges));

    printf("Held-karp:\n");
    const int pos = 0;
    const int h_k_result = held_karp(1, pos, 0);
    printf("The shortest route has cost: %d\n", h_k_result);
    printf("Here's the optimal route:\n");
    print_held_karp_route(1, pos);

    return 0;
}
