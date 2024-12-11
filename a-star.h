//
// Created by Rasmus on 11-12-2024.
//

#ifndef A_STAR_H
#define A_STAR_H

typedef struct {
    int id;
    double x, y;
} Node;

typedef struct {
    int start, end;
    double cost;
} Edge;

double a_star(Node nodes[], int num_nodes, Edge edges[], int num_edges, int start, int goal);

void print_a_star_results(const double** main_node_distances);


#endif //A_STAR_H
