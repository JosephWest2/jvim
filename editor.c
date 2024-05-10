#include "editor.h"

size_t Editor_LineLength(const EditorState *const e, int lineIndex) {
    const int endIndex = e->newlineIndexes.buffer[lineIndex];
    const int startIndex = lineIndex == 0 ? -1 : e->newlineIndexes.buffer[lineIndex - 1];
    int d = endIndex - startIndex;
    if ((int)e->text.gapIndex >= startIndex && e->text.gapIndex < endIndex) {
        d -= e->text.gapWidth;
    }
    printf("start: %d end: %d gapIndex: %zu gapWidth: %d d: %d\n", startIndex, endIndex, e->text.gapIndex,  e->text.gapWidth, d);
    return d;
}

void Editor_MoveCursor(EditorState *e, Direction direction, int distance) {

    if (direction == Right) {

        const int prev = e->cursor.effectiveCol;
        e->cursor.effectiveCol = MIN(Editor_LineLength(e, e->cursor.lineIndex) - 1, e->cursor.effectiveCol + distance);
        e->cursor.preferredCol = e->cursor.effectiveCol;
        const int offset = e->cursor.effectiveCol - prev;
        e->cursor.index += offset;

    } else if (direction == Left) {

        const int prev = e->cursor.effectiveCol;
        e->cursor.effectiveCol = MAX(e->cursor.effectiveCol - distance, 0);
        e->cursor.preferredCol = e->cursor.effectiveCol;
        const int offset = e->cursor.effectiveCol - prev;
        e->cursor.index += offset;

    } else if (direction == Up) {

        int offset = 0;
        int i = e->cursor.lineIndex;
        int min = MAX(0, i - distance);

        if (i == min) {
            return;
        }

        while (i >= min) {
            
            if (i == e->cursor.lineIndex) {
                offset += e->cursor.effectiveCol;
            } else if (i == min) {
                int length = Editor_LineLength(e, i);
                e->cursor.effectiveCol = MIN(length - 1, e->cursor.preferredCol);
                offset += length - e->cursor.effectiveCol; 
            } else {
                offset += Editor_LineLength(e, i);
            }

            i--;
        }

        e->cursor.lineIndex = min;
        e->cursor.index -= offset;

    } else if (direction == Down) {

        int offset = 0;
        int i = e->cursor.lineIndex;
        int max = MIN(e->newlineIndexes.contentLength - 1, i + distance);

        if (i == max) {
            return;
        }

        while (i <= max) {

            if (i == e->cursor.lineIndex) {
                offset += Editor_LineLength(e, i) - e->cursor.effectiveCol;
            } else if (i == max) {
                int length = Editor_LineLength(e, i);
                e->cursor.effectiveCol = MIN(length - 1, e->cursor.preferredCol);
                offset += e->cursor.effectiveCol;
            } else {
                offset += Editor_LineLength(e, i);
            }

            i++;
        }
        e->cursor.lineIndex = max;
        e->cursor.index += offset;
    }
}

void Editor_Init(EditorState *e, FILE *f) {

    e->cursor.index = 0;
    e->cursor.lineIndex = 0;
    e->cursor.effectiveCol = 0;
    e->cursor.preferredCol = 0;

    GB_Init(&e->text, f);

    ALI_Init(&e->newlineIndexes, 128);

    for (int i = 0; i < e->text.contentLength; i++) {
        if (e->text.buffer[i] == '\n') {
            ALI_Append(&e->newlineIndexes, i);
        }
    }
}
