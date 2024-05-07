#include "editor.h"
#include <stdlib.h>
#include <string.h>

void _InitTextLines(EditorState *e) {

    int prev = 0;
    int i = 0;
    for (; i < e->text.contentLength; i++) {
        if (e->text.buffer[i] == '\n') {

            ALIAppend(&e->newlineIndices, i);

            int len = i - prev + 1;

            char *s = malloc(len);
            memcpy(s, e->text.buffer + prev, len - 1);
            s[len] = '\0';

            ALSAppend(&e->textLines, s);

            prev = i;
        }
    }
}

void MoveCursorLateral(EditorState *e, Direction dir, int distance) {

    if (dir == Right) {

        e->cursor.index += distance;
        if (e->cursor.index >= e->text.contentLength) {
            e->cursor.index = e->text.contentLength - 1;
        }

    } else if (dir == Left) {

        e->cursor.index -= distance;
        if (e->cursor.index < 0) {
            e->cursor.index = 0;
        }
    }

}


void InitEditor(EditorState *e, FILE *f) {

    e->cursor.index = 0;
    e->cursor.lineIndex = 0;
    e->cursor.effectiveCol = 0;
    e->cursor.preferredCol = 0;

    InitGapBufferFromFile(&e->text, f);

    ALIInit(&e->newlineIndices, 128);

    ALSInit(&e->textLines, 128);

    _InitTextLines(e);
}
