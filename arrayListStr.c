#include "arrayListStr.h"
#include <stdio.h>
#include <stdlib.h>

static void _Grow(ArrayListStr *al) {

    al->length *= 2;
    al->buffer = realloc(al->buffer, al->length * sizeof(char *));
}

void ALS_Init(ArrayListStr *al, const unsigned int initialLength) {

    al->buffer = malloc(sizeof(int) * initialLength);
    al->length = initialLength;
    al->contentLength = 0;
}

void ALS_Append(ArrayListStr *al, char * s) {

    al->contentLength++;
    if (al->contentLength > al->length) {
        _Grow(al);
    }

    al->buffer[al->contentLength - 1] = s;
}

void ALS_Remove(ArrayListStr *al, const unsigned int index) {

    int i = index;
    al->contentLength--;
    while (i < al->contentLength) {
        al->buffer[i] = al->buffer[i + 1];
    }
}

char *ALS_Get(const ArrayListStr *const al, const unsigned int index) {

    if (index >= al->contentLength) {

        printf("HI\n");
        return 0;
    }
    return al->buffer[index];
}

void ALS_Cleanup(ArrayListStr *al) { free(al->buffer); }
