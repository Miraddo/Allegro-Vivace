// helper.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// including std libraries.
#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// including the helper header file.
#include "helper.h"

// =============================================================================
// Define the must_init function. This function is responsible for checking if a
// certain condition is met. If the condition is not met, the function will print
// an error message and exit the program.
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}