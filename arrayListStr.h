#pragma once

typedef struct ArrayListStr {
    char** buffer;
    int length;
    int contentLength;
} ArrayListStr;

void ALSInit (ArrayListStr* al, const unsigned int initialLength);

void ALSAppend (ArrayListStr* al, char* s);

void ALSRemove (ArrayListStr *al, const unsigned int index);

char* ALSGet (ArrayListStr* al, const unsigned int index);

void ALSCleanup (ArrayListStr* al);

