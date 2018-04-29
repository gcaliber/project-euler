#ifndef DIGIT_CANCELLING_FRACTIONS_H
#define DIGIT_CANCELLING_FRACTIONS_H

#include <stdint.h>
#include <stdbool.h>

#define BUFF_SIZE 10000

typedef struct {
    int numerator;
    uint8_t numerator_digits[2];
    int denominator;
    uint8_t denominator_digits[2];
} fraction_t;

bool digit_cancelling_fraction(fraction_t f);

#endif