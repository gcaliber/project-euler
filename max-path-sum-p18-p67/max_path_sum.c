#include "max_path_sum.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 1000

int max_path_sum(int **input, int row_count)
{
    node_t **triangle = malloc(sizeof(node_t *) * row_count);

    for (int row = 0; row < row_count; row++) {
        triangle[row] = malloc(sizeof(node_t) * row_count);
        for (int i = 0; i < row + 1; i++) {
            node_t *new_node = &triangle[row][i];
            new_node->value = input[row][i];
            if (row == 0) {
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->max_sum = new_node->value;
                continue;    
            }
            else {
                if (i - 1 >= 0) {
                new_node->left = &triangle[row - 1][i - 1];
                }
                else {
                    new_node->left = NULL;
                }
                if (i + 1 <= row) {
                    new_node->right = &triangle[row - 1][i];
                }
                else {
                    new_node->right = NULL;
                }
            }
            
            int left = 0;
            int right = 0;
            if (new_node->left) {
                left = new_node->left->max_sum;
            }
            if (new_node->right) {
                right = new_node->right->max_sum;
            }

            if (left >= right) {
                new_node->max_sum = new_node->value + left;
            }
            else {
                new_node->max_sum = new_node->value + right;
            }
        }
    }

    int max_path = 0;
    for (int i = 0; i < row_count; i++) {
        if (triangle[row_count - 1][i].max_sum > max_path) {
            max_path = triangle[row_count - 1][i].max_sum;
        }
    }

    for (int i = 0; i < row_count; i++) {
        free(triangle[i]);
    }
    free(triangle);
    return max_path;
}


int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: max_path_sum.out <line count> <filename>\n");
        return 1;
    }

    char *ptr;
    int row_count = strtol(argv[1], &ptr, 10);

    FILE *fp;
    fp = fopen(argv[2], "r");

    char line[MAX_BUFFER];

    char *num;
    int **triangle = malloc(sizeof(int *) * row_count);
    for(int row = 0; row < row_count; row++) {
        if (fgets(line, MAX_BUFFER, fp) == NULL) break;

        triangle[row] = malloc(sizeof(int) * row_count);
        num = strtok(line, " ");
        for (int i = 0; i < row + 1; i++) {
            int n = strtol(num, &ptr, 10);
            triangle[row][i] = n;
            num = strtok(NULL, " ");
            if (!num) break;
        }
    }
    fclose(fp);
    
    int max = max_path_sum(triangle, row_count);
    printf("Max path: %d\n", max);
    for (int i = 0; i < row_count; i++) {
        free(triangle[i]);
    }
    free(triangle);
    return 0;
}