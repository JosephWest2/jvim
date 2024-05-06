#pragma once

typedef struct {
    char *buffer;
    int length;
    int gapWidth;
    int gapIndex;
    int contentLength;
} GapBuffer;

typedef enum { Left, Right } Direction;
typedef struct __sFILE FILE;

void InitGapBuffer(GapBuffer *gb);

void InitGapBufferFromFile(GapBuffer *gb, FILE *file);

// Intended for Initialization Only
void AppendToBuffer(GapBuffer *gb, char c);

void CleanupGapBuffer(GapBuffer *gb);

void MoveGap(GapBuffer *gb, const int distance, const Direction direction);

void Insert(GapBuffer *gb, const char *const string, const int length);

void Delete(GapBuffer *gb, const Direction direction, const int amount);

void PrintBuffer(GapBuffer *gb);
