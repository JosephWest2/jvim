#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define LINE_THICKNESS 4
#define LEFT_PADDING jvs->editor.charWidth * 5
#define SPLIT_SDL_COLOR(var) var.r, var.g, var.b, var.a

void RenderBottomLine(JVIMState *jvs) {

    SDL_Rect bottomBorder;
    bottomBorder.x = 0;
    bottomBorder.y = jvs->sdl.h - jvs->editor.lineHeight - LINE_THICKNESS;
    bottomBorder.w = jvs->sdl.w;
    bottomBorder.h = LINE_THICKNESS;

    SDL_SetRenderDrawColor(jvs->sdl.renderer, SPLIT_SDL_COLOR(jvs->settings.lineColor));
    SDL_RenderFillRect(jvs->sdl.renderer, &bottomBorder);
}



void RenderText(JVIMState *jvs) {

    const int remainingHeight = jvs->sdl.h - jvs->editor.lineHeight - LINE_THICKNESS;
    jvs->editor.visibleLineCount = remainingHeight / jvs->editor.lineHeight;

    int lineY = 0;
    int i = jvs->editor.lowestVisibleLineIndex;
    while (i < jvs->editor.visibleLineCount + jvs->editor.lowestVisibleLineIndex && i + 1 < jvs->editor.fileLineCount) {
        const int lineStart = ALIGet(&jvs->editor.newlineIndices, i) + 1;
        int lineEnd;
        if (i == jvs->editor.newlineIndices.contentLength) {
            lineEnd = jvs->editor.text.contentLength - 1;
        } else {
            lineEnd = ALSGet(&jvs->editor.newlineIndices, i + 1);
        }
        if (i == jvs->editor.cursorLineIndex) {
            jvs->editor.cursorLineLength = lineEnd - lineStart;
            if (jvs->editor.preferredCursorColIndex >= jvs->editor.cursorLineLength) {
                jvs->editor.effectiveCursorColIndex = jvs->editor.cursorLineLength;
            } else {
                jvs->editor.effectiveCursorColIndex = jvs->editor.preferredCursorColIndex;
            }
        }
        char *s = " ";
        int alloc = 0;
        if (lineEnd != lineStart) {
            alloc = 1;
            s = malloc(lineEnd - lineStart + 1);
            memcpy(s, &jvs->editor.text.buffer[lineStart], lineEnd - lineStart + 1);
            s[lineEnd - lineStart] = '\0';
        }
        SDL_Surface *ts = TTF_RenderUTF8_Blended(jvs->sdl.font, s, jvs->settings.fontColor);
        SDL_Texture *tt = SDL_CreateTextureFromSurface(jvs->sdl.renderer, ts);
        SDL_Rect r;
        r.x = LEFT_PADDING;
        r.y = lineY;
        r.h = ts->h;
        r.w = ts->w;

        SDL_RenderCopy(jvs->sdl.renderer, tt, NULL, &r);

        if (alloc) {
            free(s);
        }
        SDL_FreeSurface(ts);
        SDL_DestroyTexture(tt);

        i++;
        lineY += jvs->editor.lineHeight;
    }
}

void RenderCursor(JVIMState *jvs) {

    SDL_Rect cursor;
    cursor.x = LEFT_PADDING + jvs->editor.charWidth * jvs->editor.effectiveCursorColIndex;
    cursor.y = jvs->editor.cursorLineIndex * jvs->editor.lineHeight;
    cursor.w = jvs->editor.charWidth;
    cursor.h = jvs->editor.lineHeight;

    SDL_SetRenderDrawColor(jvs->sdl.renderer, SPLIT_SDL_COLOR(jvs->settings.cursorColor));
    SDL_RenderFillRect(jvs->sdl.renderer, &cursor);
}

void Render(JVIMState *jvs) {

    SDL_SetRenderDrawColor(jvs->sdl.renderer, SPLIT_SDL_COLOR(jvs->settings.bgColor));
    SDL_RenderClear(jvs->sdl.renderer);

    jvs->editor.lineHeight = TTF_FontHeight(jvs->sdl.font);
    TTF_SizeUTF8(jvs->sdl.font, "0", &jvs->editor.charWidth, NULL);

    RenderBottomLine(jvs);

    RenderText(jvs);

    RenderCursor(jvs);

    SDL_RenderPresent(jvs->sdl.renderer);
}
