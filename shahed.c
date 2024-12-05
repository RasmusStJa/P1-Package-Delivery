#include <stdio.h>
#include <limits.h>

#define MAX 20 //SHA: Maximum number of nodes
#define INF INT_MAX
int n; //SHA: Number of nodes
int matrix[MAX][MAX]; //SHA: Adjacency matrix for distances
int memoization[1 << MAX][MAX]; //SHA: DP table for memoization
//SHA: Function to initialize the memoization table
void initialize_memoization() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            memoization[i][j] = INF;
        }
    }
}
//SHA: Function to find the minimum cost of visiting all nodes
int held_karp(int visited_nodes, int current_node) {
    //SHA: If all nodes have been visited, return to the starting node
    if (visited_nodes == (1 << n) - 1) {
        return matrix[current_node][0]; //SHA: Return to the starting node
    }
    //SHA: If this state has already been computed
    if (memoization[visited_nodes][current_node] != INF) {
        return memoization[visited_nodes][current_node];
    }
    //SHA: Explore all possible next nodes
    for (int next_nodes = 0; next_nodes < n; next_nodes++) {
        //SHA: If the city has not been visited yet
        if ((visited_nodes & (1 << next_nodes)) == 0) {
            int newCost = matrix[current_node][next_nodes] +
            held_karp(visited_nodes | (1 << next_nodes), next_nodes);
            if (newCost < memoization[visited_nodes][current_node]) {
                memoization[visited_nodes][current_node] = newCost;
            }
        }
    }
    return memoization[visited_nodes][current_node];
}

int main_sha() {
    //SHA: Input: Number of nodes
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    //SHA: Input: Adjacency matrix
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    //SHA: Initialize the memoization table
    initialize_memoization();
    // Calculate the minimum cost of the TSP
    int minCost = held_karp(1, 0); //SHA: Starting from node 0 with mask 1 (only node 0 visited)
    //SHA: Output the result
    printf("The minimum cost Hamiltonian cycle is: %d\n", minCost);
    return 0;
}