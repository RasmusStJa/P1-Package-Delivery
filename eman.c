#include <stdio.h>
#include <limits.h>
#include <math.h>
#include<stdlib.h>
#define MAX_N 20
#define INF INT_MAX
int d[MAX_N][MAX_N]; // Distance matrix
int C[MAX_N][MAX_N]; // Cost matrix
void printSubset(int S[], int size)
{
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%d", S[i]);
        if (i < size - 1) printf(", ");
    }
    printf("}\n");
}
int TSP(int n)
{
    int s, k, m;
    int opt;
    // Initialize the cost matrix for k = 2. This loop iterates over all nodes (except node 1 itself)
    // and sets the cost of traveling from node 1 to node k directly.
    for (k = 2; k <= n; k++) {
        C[1][k] = d[1][k]; /*This assigns the direct distance between node 1
        and node k (d[1][k])
        to the cost matrix C[1][k].*/
        /* example:
        * d[1][2] = 10, d[1][3] = 20, d[1][4] = 30
        After executing the loop:
        for (k = 2; k <= 4; k++) {
        C[1][k] = d[1][k];
        }*/
    }
    // Iterate through all possible subset sizes (s)
    for (s = 3; s <= n; s++)
    {
        // Iterate through all possible subsets (S) with size s
        int possible_bit= pow(2,n); //so there are 2^n possible subsets.
        int *S = (int *)malloc(s * sizeof(int)); // Array to store the current subset
        for (int i = 0; i < (possible_bit); i++) { /*This loop iterates
        through all possible bit patterns
        from 0 to 2^(n - 1).*/
            //Iterate over all subsets of {1,2,...,n}
            //('i' represents a bitmask,where each i corresponds to an element of the set.)
            /*For example, if n = 3 and i = 5 (which is 101 in binary), the
            bitmask represents the subset containing
            *elements 1 and 3 (because the 1st and 3rd bits are 1).*/
            int count = 0;/* initialised to 0. It will be used to track how
            many elements are added to the subset S.
            Count the number of set bits in i */
            for (int j = 1; j < n; j++) {//Loop over all possible elements in the set {1, 2, ..., n}
                if (i && pow(2,j)!=0) {
                    S[count++] = j;
                    // If the current subset size equals s, print the subset
                    if (count == s)
                    {
                        //to ensure that only subsets of the exact size s are printed.
                        printSubset(S, s); // Print the subset
                        free(S); // Free allocated memory
                        // Iterate through all possible ending nodes (k) within the subset
                        for (k = 1; k < s; k++) {
                            C[i][S[k]] = INF;/*For each node S[k] in the
                            current subset, the algorithm initializes the
                            minimum cost (C[i][S[k]]) as infinite (INF).*/
                            // Find the minimum cost for the current subset and ending node
                            for (m = 1; m <= n; m++) {
                                if (m != S[k] && m != 1 && ( (i && (pow(2, m -1))))) {
                                    /*If the result of (i & (pow(2, m - 1)))
                                    is non-zero (i.e., true), it means that
                                    *node m is included in the subset i.*/
                                    int min = C[(i ^ (int)pow(2, S[k] -
                                    1))][m] + d[m][S[k]];
                                    if (min < C[i][S[k]]) {
                                        C[i][S[k]] = min;
                                        /* is used to create a new subset by
                                        removing a specific node (the S[k]-th node)
                                        * from the current subset i.
                                        * The ^ operator performs bitwise XOR
                                        between i and 2^(S[k] - 1), which flips
                                        * the bit at the S[k]-th position of
                                        i.
                                        * This is used to remove the S[k]-th
                                        node from the subset represented by i.
                                        */
                                    }
                                }
                            }
                        }
                    }
                }
                // Find the minimum cost for the full tour
                opt = INF;
                for (k = 2; k <= n; k++) {
                    int min = C[(int)pow(2,n) - 1][k] + d[k][1]; /*Calculate
                    the final cost by adding the return
                    to node 1*/
                    if (min < opt) {
                        opt = min; // Track the minimum cost found
                    }
                }
                return opt; // Return the optimal cost
            }
        }
    }
}
int main(){
    int n;
    // Input the number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    // Input the distance matrix
    printf("Enter the distance matrix (row by row, with space-separated values):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &d[i][j]);
            if (i == j) {
                d[i][j] = 0; // Distance to itself is 0
            }
        }
    }
    // Call the TSP function and print the result
    int result = TSP(n);
    printf("The minimum cost of the tour is: %d\n", result);
    return 0;
}