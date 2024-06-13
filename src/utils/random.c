// random.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// including std libraries.
#include <stdlib.h>

// =============================================================================
// Define between function, which return a random number between two integers.
int between(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}

// =============================================================================
// Define between function, which return a random number between two floats.
float between_f(float lo, float hi)
{
    return lo + ((float)rand() / (float)RAND_MAX) * (hi - lo);
}