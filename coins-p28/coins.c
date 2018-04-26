#include "coins.h"
#include <stdlib.h>
#include <stdio.h>

int coins(int total)
{
    int c[total + 1];

    c[0] = 1;
    for (int i = 1; i < total + 1; i++) {
        c[i] = 0;
    }

    for (int k = 0; k < 8; k++) {
        int v = coin_values[k];
        for (int i = 0; i < total + 1 - v; i++) {
            c[i + v] += c[i];
        }
    }

    return c[total];
}

int main(int argc, char **argv)
{
    char *ptr;
    int amount = strtol(argv[1], &ptr, 10);
    int combinations = coins(amount);
    printf("There are %d ways to make %d pence.\n", combinations, amount);
    return 0;
}