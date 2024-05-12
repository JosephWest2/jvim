#pragma once

#include "shared.h"
#include "gapBuffer.h"
#include "arrayListInt.h"
#include "arrayListStr.h"

typedef struct {
    size_t index;
    int preferredCol;
    int effectiveCol;
    size_t lineIndex;
} Cursor;

typedef struct {
    Cursor cursor;
    GapBuffer text;
    // Index of the first character after a newline / begin of file
    ArrayListInt newlineIndexes;
} EditorState;

void Editor_Init(EditorState *e, FILE *f);

size_t Editor_LineLength(const EditorState *const e, int lineIndex);

void Editor_MoveCursor(EditorState *e, int offset);
