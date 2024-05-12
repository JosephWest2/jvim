#include "editor.h"

size_t Editor_LineLength(const EditorState *const e, int lineIndex) {
    const int endIndex = e->newlineIndexes.buffer[lineIndex];
    const int startIndex = lineIndex == 0 ? -1 : e->newlineIndexes.buffer[lineIndex - 1];
    int d = endIndex - startIndex;
    if ((int)e->text.gapIndex >= startIndex && e->text.gapIndex < endIndex) {
        d -= e->text.gapWidth;
    }
    printf("lineIndex: %d lineLength: %d\n", lineIndex, d);
    return d;
}

void Editor_MoveCursor(EditorState *e, int offset) {

    if (offset > 0) {

        const int prev = e->text.gapIndex;

        e->text.gapIndex = MIN(e->text.contentLength - 1, prev + offset);
        const int d = e->text.gapIndex - prev;

        for (int i = 0; i < d; i++) {
            e->text.buffer[prev + i] = e->text.buffer[prev + i + e->text.gapWidth];
            e->text.buffer[prev + i + e->text.gapWidth] = 'G';
        }

    } else if (offset < 0) {

        const int prev = e->text.gapIndex;

        e->text.gapIndex = MAX(0, prev + offset);
        const int d = e->text.gapIndex - prev;

        for (int i = 0; i > d; i--) {
            e->text.buffer[prev + e->text.gapWidth + i - 1] = e->text.buffer[prev + i - 1];
            e->text.buffer[prev + i - 1] = 'G';
        }
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
