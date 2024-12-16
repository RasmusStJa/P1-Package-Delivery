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
    for (unsigned int i = 0; i < num_nodes; i++) {
        nodes[i].id = i;
        nodes[i].x = rand() % GRID_WIDTH;
        nodes[i].y = rand() % GRID_HEIGHT;
    }

    //SHA: Print all nodes
    print_nodes(num_nodes, nodes);

    //SHA: Populate edges with costs
    int edge_count = 0;
    for (unsigned int i = 0; i < num_nodes; i++) {
        for (unsigned int j = i + 1; j < num_nodes; j++, edge_count++) {
            edges[edge_count].start = i;
            edges[edge_count].end = j;
            edges[edge_count].cost = euclidean_heuristic(nodes[i], nodes[j]);
        }
    }

    //SHA: Print results & calculate the shortest path between main nodes
    print_a_star_results(shortest_distance_main_nodes(nodes, edges));

    printf("Held-karp:\n");
    const int mask = 1, pos = 0;
    const int result = held_karp(mask, pos, 0);
    printf("The shortest route has cost: %d\n", result);
    printf("Here's the optimal route:\n");
    print_held_karp_route(mask, pos);

    return 0;
}
