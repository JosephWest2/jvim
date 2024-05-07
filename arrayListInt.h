#pragma once

typedef struct ArrayListInt {
    int* buffer;
    int length;
    int contentLength;
} ArrayListInt;

void ALIInit (ArrayListInt* al, const unsigned int initialLength);

void ALIAppend (ArrayListInt* al, const int n);

void ALIRemove (ArrayListInt *al, const unsigned int index);

int ALIGet (ArrayListInt* al, const unsigned int index);

void ALICleanup (ArrayListInt* al);

