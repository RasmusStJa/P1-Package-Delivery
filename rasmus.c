
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define MAXNODES 20
#define LINELENGTH 64
#define STDLINECOUNT 10

typedef struct node_g {  //RAS: g for graph
    char name;
    int index;
    bool visited;
    //RAS: struct node_g* neighbors[MAXNODES]; //useless for adjacency matrix
} node_g;


typedef struct edge_g {  //g for graph
    char name;
    int weight[];
} edge_g;

typedef struct hash_item {
    node_g* node;

} hash_item;


typedef struct adjacency_matrix {

    //node_g *nodes = malloc(MAXNODES * sizeof(node_g));          //RAS: array with length MAXNODES
    //int *values = malloc(MAXNODES * MAXNODES * sizeof(int));    //RAS: matrix with size MAXNODES

    node_g nodes[MAXNODES];             //RAS: array with length MAXNODES
    int values[MAXNODES][MAXNODES];     //RAS: matrix with size MAXNODES
    unsigned int size;
} adjacency_matrix;

int min(const int a, const int b) {
    if (a < b) return a;
    return b;
}

void* fillMatrix(const void* value, const int length1, const int length2) {
    void* matrix[length1][length2];
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            matrix[i][j] = value;
        }
    }
    return matrix;
}

void printAdjacencyMatrix(const adjacency_matrix *adjacency_matrix) {
    unsigned int length = sizeof(adjacency_matrix->nodes) / sizeof(adjacency_matrix->nodes[0]);

    //RAS: print every node in the same line
    printf("  "); //RAS: formatting
    for (unsigned int i = 0; i < length; i++) {
        const char node_name = adjacency_matrix->nodes[i].name;
        //RAS: while it's a letter in the alphabet (while each has been initialized
        if (!isalpha(node_name)) {
            length = i;
            break;
        }
        printf("%c ", node_name);
    }
    printf("\n");

    for (unsigned int y = 0; y < length; y++) { //RAS: column
        const char node_name = adjacency_matrix->nodes[y].name;

        for (unsigned int x = 0; x < length; x++) { //RAS: row
            //RAS: print every node on each line
            if (x == 0) { printf("%c ", node_name); }
            printf("%d ", adjacency_matrix->values[y][x]);
        }

        printf("\n");
    }
}

adjacency_matrix getFileContent(const char* fileName, char* fileContent[], char* S[], node_g* start, node_g* end) {
    char line[LINELENGTH];
    FILE *fptr = fopen(fileName, "r");
    adjacency_matrix matrix1;
    matrix1.size = 0;

    if (fptr == NULL) {
        printf("File not found\n");
        fclose(fptr);
        return matrix1;
    }

    unsigned int i = 0;
    while (fgets(line, LINELENGTH, fptr)) {  //RAS: while line is not empty (null)
        if (i == 0) {
            //RAS: if first time, get nodes (and amount)
            const unsigned int line_size = strlen(line);
            for (unsigned int j = 0; j < line_size; j++) {
                const char current_char = line[j];
                int last_space_index = 0;
                bool end_loop = false;
                switch (current_char) {
                    case ' ':
                        //RAS: this means that a new node's name starts, meaning more nodes, so increment matrix size
                        if (j != line_size - 1) { //RAS: if not last
                            matrix1.size++;
                            last_space_index = j;
                        }
                        break;
                    case '\n':
                        end_loop = true;
                        break;
                    default:

                }
                if (end_loop) { break; }
            }

            i++;
            continue;
        }
        //RAS: else get values
        fileContent[i] = line;
        i++;
    }

    fclose(fptr);
    return matrix1;
}

void saveContentInFile(const char* fileName, const adjacency_matrix* matrix1) {
    FILE* fptr = fopen(fileName, "w");

    const int (*value_matrix)[20][20] = matrix1->values;
    const unsigned int length = sizeof(value_matrix[0]) / sizeof(value_matrix[0][0]);

    for (unsigned int x = 0; x < length; x++) {
        for (unsigned int y = 0; y < length + 1; y++) {
            fprintf(fptr, "%d ", *value_matrix[x][y]);  //RAS: save for each value
        }
        fprintf(fptr, "\n");  //RAS: next line
    }

    fclose(fptr);
}

unsigned int getCost(const adjacency_matrix matrix, const node_g node1, const node_g node2) {
    return matrix.values[node1.index][node2.index];
}

void setup(const adjacency_matrix m, int *memory[20][20], const node_g S) {
    const unsigned int N = m.size;
    for (unsigned int i = 0; i < N; i++) {
        if (i == S.index) { continue; }  //RAS: skip the starting node
        //RAS: cache optimal value from S.index to i
        memory[i][1 << S.index | 1 << i] = m.values[S.index][i];
    }
}

void solve(const adjacency_matrix m, int *memory[20][20], const node_g S) {
    const unsigned int N = m.size;
    for (unsigned int r = 3; r <= N; r++) {

    }
}

void held_karp(const adjacency_matrix m, const node_g S, int *minCost, node_g* route[]) {
    //TODO: implement code from video: https://youtu.be/cY4HiiFHO1o&t=576
    const unsigned int N = m.size;

    //RAS: initialize "memory" as +inf (INT_MAX is the closest to inf)
    //RAS: memory is list of indexes of visited nodes
    int old_memory[(int)pow(2, N)] = {};
    int memory[N][(int)pow(2,N)] = { old_memory };

    setup(m, memory, S);
    solve(m, memory, S);
    minCost = findMinCost(m, memory, S);
    route = findOptimalRoute(m, memory, S);
}

int main(void) {
    adjacency_matrix matrix1;
    matrix1.size = MAXNODES;

    node_g node1; node1.name = 'A';
    node_g node2; node2.name = 'B';

    matrix1.nodes[0].name = 'A'; matrix1.nodes[0].index = 1;
    matrix1.nodes[1].name = 'B'; matrix1.nodes[1].index = 2;
    matrix1.nodes[1].name = 'C'; matrix1.nodes[1].index = 3;

    matrix1.nodes->visited = false;

    matrix1.values[0][0] = 0; matrix1.values[0][1] = 1; matrix1.values[0][2] = 2;
    matrix1.values[1][0] = 1; matrix1.values[1][1] = 0; matrix1.values[1][2] = 1;
    matrix1.values[2][0] = 2; matrix1.values[2][1] = 1; matrix1.values[2][2] = 0;

    char* inputContent[STDLINECOUNT][LINELENGTH]; //RAS: array length * max string length * character size
    //getFileContent("input.txt", inputContent);

    printAdjacencyMatrix(&matrix1);

    //printFileContent("input.txt");
    return 0;
}
