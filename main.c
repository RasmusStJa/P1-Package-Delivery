#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "held-karp.h"
#include "a-star.h"

int main() {
    printf("A-star:\n");

    srand(time(NULL)); //random number generator based on current time

    //Define the intermediate graph
    const unsigned int num_nodes = NUM_INTERMEDIATE_NODES * NUM_MAIN_NODES;
    Node nodes[num_nodes];
    Edge edges[num_nodes * num_nodes];

    //Populate nodes with random coordinates
    populate_nodes(nodes, num_nodes);

    print_nodes(num_nodes, nodes);

    //Populate edges with costs
    populate_edges(edges, nodes, num_nodes);

    //Calculate the shortest path between main nodes
    const unsigned int edge_count = num_nodes * (num_nodes + 1) / 2; //RAS: look at line 157-158 in a-star.c
    double main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES];
    for (unsigned int i = 0; i < NUM_MAIN_NODES; i++) {
        for (unsigned int j = i + 1; j < NUM_MAIN_NODES; j++) {
            const int start = i * NUM_INTERMEDIATE_NODES;
            const int goal = j * NUM_INTERMEDIATE_NODES + NUM_INTERMEDIATE_NODES - 1;
            main_node_distances[i][j] = a_star(nodes, num_nodes, edges, edge_count, start, goal);
            main_node_distances[j][i] = main_node_distances[i][j]; //Symmetric
        }
    }

    //Print results
    print_a_star_results(main_node_distances);

    printf("\nHeld-karp:\n");
    const int pos = 0;
    const double h_k_distance = held_karp(main_node_distances, 1 << pos, pos, 0);
    printf("Optimal route:\n");
    print_held_karp_route(pos, " -> ");
    printf("Distance: %.2f\n", h_k_distance);

    return 0;
}
