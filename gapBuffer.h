#pragma once

#include <stdbool.h>

typedef struct GapBuffer {
    char *buffer;
    int length;
    int gapWidth;
    int gapIndex;
    int contentLength;
} GapBuffer;

typedef struct _IO_FILE FILE;

void InitGapBuffer(GapBuffer *gb);

void InitGapBufferFromFile(GapBuffer *gb, FILE *file);

// Intended for Initialization Only
void AppendToBuffer(GapBuffer *gb, char c);

void CleanupGapBuffer(GapBuffer *gb);

void MoveGap(GapBuffer *gb, const int distance, Direction1D direction);

void Insert(GapBuffer *gb, const char *const string, const int length);

void Delete(GapBuffer *gb, Direction1D direction, const int amount);

void PrintBuffer(GapBuffer *gb);
