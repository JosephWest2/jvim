#include "gapBuffer.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_LENGTH 1024
#define DEFAULT_GAP_WIDTH 12
#define MAX_GAP_WIDTH 24

void InitGapBuffer(GapBuffer *gb) {

    gb->buffer = malloc(INITIAL_LENGTH);
    gb->length = INITIAL_LENGTH;
    gb->gapWidth = DEFAULT_GAP_WIDTH;
    gb->gapIndex = 0;
    gb->contentLength = DEFAULT_GAP_WIDTH;
}

void _Grow(GapBuffer *gb) {
    gb->length *= 2;
    gb->buffer = realloc(gb->buffer, gb->length);
}

void AppendToBuffer(GapBuffer *gb, char c) {

    gb->contentLength++;
    if (gb->contentLength == gb->length) {
        _Grow(gb);
    }
    gb->buffer[gb->contentLength - 1] = c;
}

void InitGapBufferFromFile(GapBuffer *gb, FILE *file) {

    InitGapBuffer(gb);
    while (1) {
        char c = fgetc(file);
        if (feof(file)) {
            break;
        }
        AppendToBuffer(gb, c);
    }
}

void CleanupGapBuffer(GapBuffer *gb) { free(gb->buffer); }

void MoveGap(GapBuffer *gb, int distance, Direction1D direction) {
    const int prev = gb->gapIndex;

    if (direction == left) {

        if (gb->gapIndex - distance > 0) {
            gb->gapIndex -= distance;
        } else {
            gb->gapIndex = 0;
        }

    } else if (direction == Up) {

        if (gb->gapIndex + distance < gb->length - gb->gapWidth) {
            gb->gapIndex += distance;
        } else {
            gb->gapIndex = gb->length - gb->gapWidth;
        }
    }

    int i = 0;
    while (i < gb->gapWidth) {
        gb->buffer[prev + i] = gb->buffer[gb->gapIndex + i];
        i++;
    }
}

void _ExpandGap(GapBuffer *gb, const int amount) {

    if (gb->contentLength + amount > gb->length) {
        _Grow(gb);
    }

    int i = gb->contentLength - 1;
    while (i >= gb->gapIndex + gb->gapWidth) {
        gb->buffer[i + amount] = gb->buffer[i];
        i--;
    }
    gb->gapWidth += amount;
}

void Insert(GapBuffer *gb, const char *const string, const int length) {

    if (gb->gapWidth < length) {
        _ExpandGap(gb, length - gb->gapWidth + DEFAULT_GAP_WIDTH);
    }
    memcpy(gb->buffer + gb->gapIndex, string, length);
    gb->gapWidth -= length;
    gb->gapIndex += length;
}

void Delete(GapBuffer *gb, const Direction direction, const int amount) {

    if (direction == Right) {
        if (gb->gapIndex + gb->gapWidth >= gb->contentLength) {
            gb->gapWidth = gb->contentLength - gb->gapIndex - 1;
        } else {
            gb->gapWidth += amount;
        }
    } else if (direction == Left) {
        if (gb->gapIndex - amount <= 0) {
            gb->gapIndex = 0;
        } else {
            gb->gapIndex -= amount;
        }
    }

    // Probably unneccesary
    if (gb->gapWidth > MAX_GAP_WIDTH) {

        const int d = MAX_GAP_WIDTH - gb->gapWidth;
        int i = gb->gapIndex + gb->gapWidth;
        while (i < gb->contentLength) {
            gb->buffer[i - d] = gb->buffer[i];
            i++;
        }
        gb->contentLength -= d;
    }
}

void PrintBuffer(GapBuffer *gb) {

    int i = 0;
    while (i < gb->contentLength) {
        printf("%c", gb->buffer[i]);
        i++;
    }
}
