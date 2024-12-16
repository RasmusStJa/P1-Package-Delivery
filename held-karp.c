#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LOCATIONS 20 //ABD: Jeg har taget udgangspunkt i eksemplet, som består af 4 lokationer, dette skal ændres når matri

#define INF INT_MAX
/*ABD:
 *Definerer INF som den største mulige integer-værdi (INT_MAX).
 *Det bruges til at repræsentere "uendelig", når en sti ikke er
 *mulig. */

//RAS: example of a size 20 matrix (completely random distances, except from a node to itself)

int dist[MAX_LOCATIONS][MAX_LOCATIONS] = {
    {0, 2, 5, 12, 10, 15, 12, 5, 7, 8, 8, 6, 9, 5, 14, 11, 14, 4, 3, 3},
    {2, 0, 4, 9, 15, 13, 12, 15, 5, 5, 6, 9, 11, 4, 5, 2, 14, 6, 1, 13},
    {7, 8, 0, 3, 4, 12, 4, 1, 6, 9, 5, 5, 12, 3, 11, 8, 10, 12, 15, 9},
    {7, 5, 10, 0, 6, 13, 8, 9, 11, 10, 5, 6, 14, 5, 14, 14, 2, 7, 1, 14},
    {5, 11, 5, 10, 0, 7, 8, 8, 12, 1, 1, 6, 2, 12, 4, 6, 14, 8, 6, 10},
    {3, 11, 13, 8, 6, 0, 12, 11, 3, 1, 11, 8, 6, 1, 14, 2, 6, 6, 9, 6},
    {14, 11, 6, 5, 11, 9, 0, 5, 3, 1, 2, 3, 11, 8, 9, 7, 5, 5, 15, 9},
    {3, 15, 11, 7, 12, 9, 12, 0, 10, 1, 12, 5, 7, 13, 3, 4, 12, 15, 14, 2},
    {3, 12, 6, 5, 3, 14, 7, 11, 0, 6, 2, 12, 5, 2, 15, 10, 1, 12, 10, 5},
    {3, 12, 14, 4, 8, 11, 1, 7, 15, 0, 12, 8, 7, 1, 10, 12, 11, 13, 9, 3},
    {4, 7, 10, 4, 5, 8, 9, 3, 11, 5, 0, 7, 1, 11, 3, 14, 9, 11, 3, 10},
    {13, 14, 1, 3, 8, 6, 13, 3, 4, 2, 13, 0, 6, 9, 12, 7, 11, 15, 8, 8},
    {4, 11, 1, 12, 14, 3, 7, 9, 15, 15, 14, 4, 0, 15, 14, 11, 5, 5, 11, 8},
    {9, 8, 9, 10, 6, 1, 7, 13, 13, 15, 5, 15, 2, 0, 11, 2, 3, 3, 5, 8},
    {9, 10, 14, 5, 9, 2, 8, 3, 9, 12, 9, 1, 4, 14, 0, 1, 1, 7, 7, 4},
    {9, 10, 10, 12, 3, 5, 11, 4, 12, 13, 2, 14, 15, 8, 10, 0, 5, 5, 12, 9},
    {4, 15, 11, 4, 4, 14, 1, 9, 6, 2, 11, 15, 1, 9, 6, 3, 0, 11, 7, 1},
    {10, 14, 14, 15, 6, 7, 14, 5, 6, 8, 6, 6, 6, 14, 2, 12, 15, 0, 15, 6},
    {13, 2, 8, 12, 13, 14, 6, 15, 11, 9, 7, 15, 4, 5, 6, 15, 15, 14, 0, 8},
    {3, 3, 9, 3, 15, 4, 9, 12, 9, 13, 6, 2, 13, 6, 9, 13, 12, 11, 9, 0}
};

int dp[1 << MAX_LOCATIONS][MAX_LOCATIONS]; //ABD: matrix, der gemmer de mindste omkostninger.
int parents[1 << MAX_LOCATIONS][MAX_LOCATIONS]; //RAS: matrix of chosen path
int n = MAX_LOCATIONS; //ABD: Beregner , som bruges til at repræsentere alle mulige undergrupper af lokationer.

//ABD
int held_karp(const int mask, const int pos, unsigned int iteration) {
    //RAS: only run the first time
    if (iteration == 0) {
        //RAS: correctly initializes the matrix
        for (unsigned int i = 0; i < (1 << n); i++) {
            for (unsigned int j = 0; j < n; j++) {
                dp[i][j] = -1;
            }
        }
    }

    //RAS: if done
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    //RAS: if cost is not defined
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF, bestCity = -1;

    for (unsigned int destination = 0; destination < n; destination++) {
        if (!(mask & (1 << destination))) {
            const int newAns = dist[pos][destination] + held_karp(mask | (1 << destination), destination, ++iteration);
            //RAS: if cost is lower, update ans and best city
            if (newAns < ans) {
                ans = newAns;
                bestCity = destination;
            }
        }
    }

    dp[mask][pos] = ans;
    parents[mask][pos] = bestCity;
    return ans;
}

void print_held_karp_route(int mask, int pos) {
    const int start = pos;
    const char *between = " -> ";

    printf("%d%s", start, between);

    //RAS: print for every node
    while (mask != (1 << n) - 1) {
        //RAS: while all destinations haven't been visited
        const int nextDest = parents[mask][pos]; //RAS: get next city

        printf("%d%s", nextDest, between);

        mask |= 1 << nextDest; //RAS: mark as visited
        pos = nextDest; //RAS: update position
    }
    //RAS: go back to the start
    printf("%d\n", start);
}
/*
int main() {
    //ABD: Step 2.
    const int mask = 1, pos = 0;
    const int result = held_karp(mask, pos);
    printf("The shortest path has cost: %d\n", result);
    printf("Here's the optimal route:\n");
    printRoute(mask, pos);
    return 0;
}*/
