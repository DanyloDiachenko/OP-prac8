#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MIN_INDUCTANCE 0
#define MAX_INDUCTANCE 1e3

#define MIN_CAPACITANCE 0
#define MAX_CAPACITANCE 1e5

#define MIN_RESISTANCE 1e-2
#define MAX_RESISTANCE 1e6

#define MIN_FREQUENCY 1
#define MAX_FREQUENCY 1e10

#define MIN_FREQUENCY_STEP 1e-1
#define MAX_FREQUENCY_STEP 1e3

typedef struct
{
    double real;
    double imaginary;
} Complex;

#endif // CONSTANTS_H
