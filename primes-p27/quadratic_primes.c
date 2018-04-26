#include "quadratic_primes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int quadratic_abs(int n, int a, int b)
{
    return abs((n * n) + (a * n) + b);
}

int count_quadratic_primes(int a, int b, int limit, bool* primes)
{
    int i = 1;
    int test;
    do {
        test = quadratic_abs(i, a, b);
        i++;
    } while (primes[test]);
    return i - 1;
}

int max_quadratic_primes(int limit, int *max_a, int *max_b)
{
    bool primes[limit + 1];
    for (int i = 0; i <= limit; i++) {
        primes[i] = true;
    }
    primes[0] = false;
    primes[1] = false;

    for (int p = 2; p <= limit; p++) {
        while (!primes[p]) p++;
        for (int i = p + p; i <= limit; i += p) {
            primes[i] = false;
        }
    }

    int max_consecutive_primes = 0;
    for (int a = (limit * -1 + 1); a < limit; a++) {
        if (a == 0) continue;
        int b = 2;
        while(b <= limit) {
            int prime_count = count_quadratic_primes(a, b, limit, primes);
            if (max_consecutive_primes < prime_count) {
                max_consecutive_primes = prime_count;
                *max_a = a;
                *max_b = b;
            }
            prime_count = count_quadratic_primes(a, (b * -1), limit, primes);
            if (max_consecutive_primes < prime_count) {
                max_consecutive_primes = prime_count;
                *max_a = a;
                *max_b = b * -1;
            }
            b++;
            while (!primes[b] && b <= limit) b++;
        }
    }
    return max_consecutive_primes;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <limit>\n", argv[0]);
        return 1;
    }
    char *ptr;
    int limit = strtol(argv[1], &ptr, 10);
    if (limit <= 0) {
        fprintf(stderr, "Limit cannot be less than 1.\n");
        return 1;
    }

    int a = 0;
    int b = 0;
    int max_primes = max_quadratic_primes(limit, &a, &b);
    printf("n^2 + a*n + b has %d consecutive primes for |a| < %d and |b| <= %d\n", max_primes, limit - 1, limit);
    printf("when a is %d and b is %d.\n", a, b);
    printf("%d * %d = %d\n", a, b, a * b);
    return 0;
}