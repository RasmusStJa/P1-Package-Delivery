#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "a-star.h"

#define MAX_LOCATIONS 20
#define INF INT_MAX

int dp[1 << NUM_MAIN_NODES][NUM_MAIN_NODES]; //lowest costs
int parents[1 << NUM_MAIN_NODES][NUM_MAIN_NODES]; //matrix of chosen path
int n = NUM_MAIN_NODES; //represents subgroups of locations

double held_karp(double main_node_distances[NUM_MAIN_NODES][NUM_MAIN_NODES], const int mask, const int pos, unsigned int iteration) {
    if (iteration == 0) {
        for (unsigned int i = 0; i < (1 << n); i++) {
            for (unsigned int j = 0; j < n; j++) {
                dp[i][j] = -1;
            }
        }
    }

    if (mask == (1 << n) - 1) {
        return main_node_distances[pos][0];
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    double ans = INF, bestDestination = -1;

    for (unsigned int destination = 0; destination < n; destination++) {
        if (!(mask & (1 << destination))) {
            const double newAns = main_node_distances[pos][destination] + held_karp(main_node_distances, mask | (1 << destination), destination, ++iteration);
            if (newAns < ans) {
                ans = newAns;
                bestDestination = destination;
            }
        }
    }

    dp[mask][pos] = ans;
    parents[mask][pos] = bestDestination;

    return ans;
}

void print_held_karp_route(int pos, const char between[]) {
    int mask = 1;
    const int start = pos;

    printf("%d%s", start, between);

    //print for every node
    while (mask != (1 << n) - 1) {
        //while all destinations haven't been visited
        const int nextDest = parents[mask][pos]; //get next destination

        printf("%d%s", nextDest, between);

        mask |= 1 << nextDest; //mark as visited
        pos = nextDest; //update position
    }
    //go back to the start
    printf("%d\n", start);
}
