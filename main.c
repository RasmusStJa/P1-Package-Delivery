#include <stdio.h>

struct node {
    char name;
    int cost;
    struct node neighbors[];
    int weight[];
};

int main(void) {
    struct node A;
    A.name = 'A';

    printf("Hello World!");
    return 0;
}