#include "arrayList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitArrayList(ArrayList *al, const unsigned int initialLength) {

    al->buffer = malloc(sizeof(int) * initialLength);
    al->length = initialLength;
    al->contentLength = 0;
}

void Grow(ArrayList *al) {

    int *temp = malloc(al->length * 2 * sizeof(int));
    memcpy(temp, al->buffer, al->length * sizeof(int));
    al->buffer = temp;
    al->length *= 2;
}

void Append(ArrayList *al, const int n) {

    al->contentLength++;
    if (al->contentLength > al->length) {
        Grow(al);
    }

    al->buffer[al->contentLength-1] = n;
}

void Remove(ArrayList *al, const unsigned int index) {

    int i = index;
    al->contentLength--;
    while (i < al->contentLength) {
        al->buffer[i] = al->buffer[i + 1];
    }
}

int ALGet(ArrayList* al, const unsigned int index) {

    if (index >= al->contentLength) {
        printf("ARRAYLIST INDEX OUT OF BOUNDS ATTEMPT");
        exit(EXIT_FAILURE);
        return 0;
    }
    return al->buffer[index];

}

void CleanupArraylist(ArrayList* al) {

    free(al->buffer);
}
