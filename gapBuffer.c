#include "gapBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_LENGTH 1024
#define DEFAULT_GAP_WIDTH 12

static void _Grow(GapBuffer *gb) {
    gb->length *= 2;
    gb->buffer = realloc(gb->buffer, gb->length);
}

static void _InitAppendToBuffer(GapBuffer *gb, char c) {

    gb->contentLength++;
    if (gb->contentLength == gb->length) {
        _Grow(gb);
    }
    gb->buffer[gb->contentLength - 1] = c;
}

static void _ExpandGap(GapBuffer *gb, const int amount) {

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

void GB_Init(GapBuffer *gb, FILE *file) {

    gb->buffer = malloc(INITIAL_LENGTH);
    gb->length = INITIAL_LENGTH;
    gb->gapWidth = DEFAULT_GAP_WIDTH;
    gb->gapIndex = 0;
    gb->contentLength = DEFAULT_GAP_WIDTH;
    while (1) {
        char c = fgetc(file);
        if (feof(file)) {
            break;
        }
        _InitAppendToBuffer(gb, c);
    }
}

void GB_Free(GapBuffer *gb) {
    free(gb->buffer);
    gb = NULL;
}

void GB_MoveGap(GapBuffer *gb, const int distance, const Direction direction) {
    const int prev = gb->gapIndex;

    if (direction == Left) {

        if (gb->gapIndex - distance > 0) {
            gb->gapIndex -= distance;
        } else {
            gb->gapIndex = 0;
        }

    } else if (direction == Right) {

        if (gb->gapIndex + distance < gb->length - gb->gapWidth) {
            gb->gapIndex += distance;
        } else {
            gb->gapIndex = gb->length - gb->gapWidth;
        }
    } else {
        printf("Invalid Direction Input GB_MoveGap");
        return;
    }

    int i = 0;
    while (i < gb->gapWidth) {
        gb->buffer[prev + i] = gb->buffer[gb->gapIndex + i];
        i++;
    }
}

void GB_Insert(GapBuffer *gb, const char *const string, const int length) {

    if (gb->gapWidth < length) {
        _ExpandGap(gb, length - gb->gapWidth + DEFAULT_GAP_WIDTH);
    }
    memcpy(gb->buffer + gb->gapIndex, string, length);
    gb->gapWidth -= length;
    gb->gapIndex += length;
}

void GB_Delete(GapBuffer *gb, const Direction direction, const int amount) {

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
}

void GB_Print(const GapBuffer *const gb) {

    int i = 0;
    while (i < gb->contentLength) {
        printf("%c", gb->buffer[i]);
        i++;
    }
}
