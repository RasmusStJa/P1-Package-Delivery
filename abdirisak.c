#include <stdio.h>
#include <limits.h>

#define MAX_LOCATIONS 4 // Jeg har taget udgangspunkt i eksemplet, som består af 4 lokationer, dette skal ændres når matri
#define INF INT_MAX
/*Definerer INF som den største mulige integer-værdi (INT_MAX).
*Det bruges til at repræsentere "uendelig", når en sti ikke er
mulig. */

// Definerer en matrix, hvor dist[i][j] repræsenterer afstanden mellem lokation i og j.
// HUSK DEN FØRSTE ROW OG COLUMN ER ROW 0 OG COLUMN 0
int dist[MAX_LOCATIONS][MAX_LOCATIONS] = {
    {0, 1, 15, 6},
    {2, 0, 7, 3},
    {9, 6, 0, 12},
    {10, 4, 8, 0}
};

int dp[1 << MAX_LOCATIONS][MAX_LOCATIONS]; // array, der gemmer de mindste omkostninger.
int n = MAX_LOCATIONS; // Beregner , som bruges til at repræsentere alle mulige undergrupper af lokationer.

int tsp(int mask, int pos) {

    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;


    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city),
            city);
            if (newAns < ans) {
                ans = newAns;
            }
        }
    }

    dp[mask][pos] = ans;
    return ans;
}

int main() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    // Step 2.
    int result = tsp(1, 0);
    printf("The shortest path has cost: %d\n", result);
    return 0;
}