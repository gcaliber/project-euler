#ifndef MAX_PATH_SUM_H
#define MAX_PATH_SUM_H

typedef struct node {
    int value;
    int max_sum;
    struct node *left;
    struct node *right;
} node_t;

int max_path_sum(int **pyramid, int base);

#endif