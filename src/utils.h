#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int team_id_t;

#define MALLOC(type, len) malloc(sizeof(type) * (len))

#define CHECK_PTR(ptr, func) \
do { \
    if(ptr == NULL) { \
        perror(#func "() invoked for pointer " #ptr); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

// Generates a number between 0 and max included
#define RAND_GENERATOR(max) rand() % (max + 1)

#define IS_ODD(n) (((n) % 2) == 1)