//
// Created by rasmu on 11-12-2024.
//

#ifndef HELD_KARP_H
#define HELD_KARP_H

#include "a-star.h"

int held_karp(double main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES], int mask, const int pos, unsigned int iteration);
void print_held_karp_route(int pos, char between[]);

#endif //HELD_KARP_H
