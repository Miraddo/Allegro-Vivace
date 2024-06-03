//
// Created by miraddo on 6/2/2024.
// helper.c
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}