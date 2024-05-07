#pragma once

#include "main.h"
#include "gapBuffer.h"
#include "arrayListInt.h"
#include "arrayListStr.h"

typedef struct {
    int index;
    int preferredCol;
    int effectiveCol;
    int lineIndex;
} Cursor;

typedef struct {
    Cursor cursor;
    GapBuffer text;
    ArrayListInt newlineIndices;
    ArrayListStr textLines;
} EditorState;

void InitEditor(EditorState *e, FILE *f);

void MoveCursor(EditorState *e, Direction2D dir, int offset);
