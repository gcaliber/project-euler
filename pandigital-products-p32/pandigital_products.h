#ifndef PANDIGITAL_PRODUCTS_H
#define PANDIGITAL_PRODUCTS_H

#define MIN_PRODUCTS 1000

typedef struct {
    int multiplicand;
    int multiplier;
    int product;
} product_t;

int pandigital_products(const char *digits, product_t **solutions);

#endif