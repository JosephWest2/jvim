#pragma once

#include "shared.h"
#include <stdio.h>

typedef struct GapBuffer {
    char *buffer;
    size_t length;
    int gapWidth;
    size_t gapIndex;
    size_t contentLength;
} GapBuffer;

void GB_Init(GapBuffer *gb, FILE *file);

void GB_Free(GapBuffer *gb);

void GB_MoveGap(GapBuffer *gb, const int distance, const Direction direction);

void GB_Insert(GapBuffer *gb, const char *const string, const int length);

void GB_Delete(GapBuffer *gb, const Direction direction, const int amount);

void GB_Print(const GapBuffer *const gb);
