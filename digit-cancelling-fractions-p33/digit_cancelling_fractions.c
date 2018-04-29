#include "digit_cancelling_fractions.h"
#include <stdio.h>
#include <stdlib.h>

int get_gcd(int a, int b)
{
    if (a == 0 || b == 0) return 1;
    if (a == b) return a;
    if (a > b)  return get_gcd(a - b, b);
    return get_gcd(a, b - a);
}

bool digit_cancelling_fraction(fraction_t f)
{
    int match = -1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (f.numerator_digits[i] == f.denominator_digits[j]) 
                match = f.numerator_digits[i];
        }
    }
    
    if (match == -1) return false;
    
    int new_n, new_d;
    for (int i = 0; i < 2; i++) {
        if (f.numerator_digits[i] != match) 
            new_n = f.numerator_digits[i];
        if (f.denominator_digits[i] != match) 
            new_d = f.denominator_digits[i];
    }
    
    int gcd = get_gcd(f.numerator, f.denominator);
    int new_gcd = get_gcd(new_n, new_d);

    if (gcd != new_gcd && f.numerator / gcd == new_n / new_gcd && f.denominator / gcd == new_d / new_gcd)
        return true;
    return false;
}

int build_test_fractions(fraction_t **fractions) {
    *fractions = malloc(BUFF_SIZE * (sizeof(fraction_t)));
    fraction_t *f = *fractions;
    int fraction_count = 0;
    for (int i = 11; i < 99; i++) {
        if (i % 10 == 0) continue;
        for (int j = i + 1; j < 100; j++) {
            if (j % 10 == 0) continue;
            f[fraction_count].numerator = i;
            f[fraction_count].denominator = j;
            f[fraction_count].numerator_digits[0] = i / 10;
            f[fraction_count].numerator_digits[1] = i % 10;
            f[fraction_count].denominator_digits[0] = j / 10;
            f[fraction_count].denominator_digits[1] = j % 10;
            fraction_count++;
        }
    }
    return fraction_count;
}

int main(void)
{
    fraction_t *fractions = NULL;
    int fraction_count = build_test_fractions(&fractions);

    int n_product = 1;
    int d_product = 1;
    for (int i = 0; i < fraction_count; i++) {
        bool is_dcf = digit_cancelling_fraction(fractions[i]);
        if (is_dcf) {
            printf("%d/%d\n", fractions[i].numerator, fractions[i].denominator);
            n_product *= fractions[i].numerator;
            d_product *= fractions[i].denominator;
        }
    }
    int gcd = get_gcd(n_product, d_product);
    printf("product: %d/%d\n", n_product / gcd, d_product / gcd);

    return 0;
}