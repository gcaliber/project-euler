#include "pandigital_products.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void build_trie(node_t *self, const char *str)
{
    if (!self) return;

    int len = strlen(str);
    self->child_count = len - 1;
    self->children = calloc(self->child_count, sizeof(node_t));
    for (int i = 0; i < len; i++) {
        strncpy(self->c, &str[i], 1);
        if (len > 1) {
            char rest[len];
            strncpy(rest, str, i);
            strncat(rest, &str[i + 1], len - i - 1);
            printf("head: %s   rest: %s\n", self->c, rest);
            build_trie(&self->children[i], rest);
        } else {
            self->children = NULL;
        }
    }
}

void combine(node_t *self, char *acc, int *entry_count, char **result)
{
    if (!self) {
        strcpy(result[(*entry_count)++], acc);
        return;
    }
    
    char new_acc[10];
    strcpy(new_acc, acc);
    strcat(new_acc, self->c);
    for (int i = 0; i < self->child_count; i++) {
        combine(&self->children[i], new_acc, entry_count, result);
    }
}

char **find_combinations(const char *str)
{
    int len = strlen(str);
    node_t root;
    root.child_count = len;
    root.children = malloc(root.child_count * sizeof(node_t));
    strcpy(root.c, "");
    for (int i = 0; i < len; i++) {
        // printf("called %d times\n", i + 1);
        build_trie(&root.children[i], str);
    }

    // printf("finished building trie\n");
    int comb_count = 1;
    for (int i = 1; i <= root.child_count; i++) {
        comb_count *= i;
    }
    char **result = malloc(comb_count * sizeof(char *));
    int entry_count = 0;
    char acc[len + 1];
    for (int i = 0; i <= len; i++) {
        acc[i] = '\0';
    }
    combine(&root, acc, &entry_count, result);

    for (int i = 0; i < entry_count; i++) {
        printf("%s\n", result[i]);
    }

    return result;
}

int pandigital_products(const char *digits, product_t **solutions)
{
    char **combinations = find_combinations(digits);
    return 0;
}

int main(int argc, char **argv) {
    product_t *solutions = NULL;
    int solution_count = pandigital_products(argv[1], &solutions);
    return 0;
}