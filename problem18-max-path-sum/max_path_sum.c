#include "max_path_sum.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max_path_sum(int **input, int base)
{
    node_t **pyramid = malloc(sizeof(node_t *) * base);

    for (int row = 0; row < base; row++) {
        pyramid[row] = malloc(sizeof(node_t) * base);
        for (int i = 0; i < row + 1; i++) {
            node_t *new_node = &pyramid[row][i];
            new_node->value = input[row][i];
            if (row == 0) {
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->max_sum = new_node->value;
                // printf("[%d][%d] v: %d  m: %d    ", row, i, new_node->value, new_node->max_sum);
                continue;    
            }
            else {
                if (i - 1 >= 0) {
                new_node->left = &pyramid[row - 1][i - 1];
                }
                else {
                    new_node->left = NULL;
                }
                if (i + 1 <= row) {
                    new_node->right = &pyramid[row - 1][i];
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
            // printf("[%d][%d] v: %d  m: %d    ", row, i, new_node->value, new_node->max_sum);
        }
        // printf("\n");
    }

    int max_path = 0;
    for (int i = 0; i < base; i++) {
        // printf("%d, ", pyramid[base - 1][i].max_sum);
        if (pyramid[base - 1][i].max_sum > max_path) {
            max_path = pyramid[base - 1][i].max_sum;
        }
    }
    // printf("\n");
    return max_path;
}





int main(void) {

    int rows = 15;

    char str[500] = "75 "
                    "95 64 "
                    "17 47 82 "
                    "18 35 87 10 "
                    "20 04 82 47 65 "
                    "19 01 23 75 03 34 "
                    "88 02 77 73 07 63 67 "
                    "99 65 04 28 06 16 70 92 "
                    "41 41 26 56 83 40 80 70 33 "
                    "41 48 72 33 47 32 37 16 94 29 "
                    "53 71 44 65 25 43 91 52 97 51 14 "
                    "70 11 33 28 77 73 17 78 39 68 17 57 "
                    "91 71 52 38 17 14 91 43 58 50 27 29 48 "
                    "63 66 04 68 89 53 67 30 73 16 69 87 40 31 "
                    "04 62 98 27 23 09 70 98 73 93 38 53 60 04 23 ";

    int **pyramid = malloc(sizeof(int *) * rows);
        
    char *token;
    token = strtok(str, " ");
    int row = 0;
    while( token != NULL ) {
        pyramid[row] = malloc(sizeof(int) * rows);

        for (int i = 0; i < row + 1; i++) {
            char *ptr;
            int n = strtol(token, &ptr, 10);
            pyramid[row][i] = n;
            token = strtok(NULL, " ");
            if (!token) break;
        }
        row++;
    }

    // for (int row = 0; row < rows; row++) {
    //     for (int i = 0; i < row + 1; i++) {
    //         printf("%d ", pyramid[row][i]);
    //     }
    //     printf("\n");
    // } 

    int max = max_path_sum(pyramid, rows);
    printf("max path is %d\n", max);
    return 0;
}