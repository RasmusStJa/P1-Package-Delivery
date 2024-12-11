#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "held-karp.h"
#include "a-star.h"

int main() {
    printf("A-star:\n");
    //srand(time(NULL)); //SHA: Seed the random number generator with the current time

    printf("Held-karp:\n");
    const int mask = 1, pos = 0;
    const int result = held_karp(mask, pos, 0);
    printf("The shortest path has cost: %d\n", result);
    printf("Here's the optimal route:\n");
    print_held_karp_route(mask, pos);

    return 0;
}
