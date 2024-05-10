#pragma once

#include <stddef.h>

typedef struct ArrayListStr {
    char **buffer;
    size_t length;
    size_t contentLength;
} ArrayListStr;

void ALS_Init(ArrayListStr *al, const unsigned int initialLength);

void ALS_Append(ArrayListStr *al, char *s);

void ALS_Remove(ArrayListStr *al, const unsigned int index);

char *ALS_Get(const ArrayListStr *const al, const unsigned int index);

void ALS_Free(ArrayListStr *al);
