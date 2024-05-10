#pragma once

#include <stddef.h>

typedef struct ArrayListInt {
    int *buffer;
    size_t length;
    size_t contentLength;
} ArrayListInt;

void ALI_Init(ArrayListInt *al, const unsigned int initialLength);

void ALI_Append(ArrayListInt *al, const int n);

void ALI_Remove(ArrayListInt *al, const unsigned int index);

int ALI_Get(const ArrayListInt *const al, const unsigned int index);

void ALI_Free(ArrayListInt *al);
