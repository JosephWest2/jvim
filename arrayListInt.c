#include "arrayListInt.h"
#include <stdio.h>
#include <stdlib.h>

void ALIInit (ArrayListInt *al, const unsigned int initialLength) {

    al->buffer = malloc(sizeof(int) * initialLength);
    al->length = initialLength;
    al->contentLength = 0;
}

void _Grow (ArrayListInt *al) {

    al->length *= 2;
    al->buffer = realloc(al->buffer, sizeof(int) * al->length);
}

void ALIAppend (ArrayListInt *al, const int n) {

    al->contentLength++;
    if (al->contentLength > al->length) {
        _Grow(al);
    }

    al->buffer[al->contentLength - 1] = n;
}

void ALIRemove (ArrayListInt *al, const unsigned int index) {

    int i = index;
    al->contentLength--;
    while (i < al->contentLength) {
        al->buffer[i] = al->buffer[i + 1];
    }
}

int ALIGet (ArrayListInt *al, const unsigned int index) {

    if (index >= al->contentLength) {

        printf("HI\n");
        return 0;
    }
    return al->buffer[index];
}

void ALICleanup (ArrayListInt *al) { free(al->buffer); }
