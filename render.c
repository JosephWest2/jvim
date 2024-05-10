#include "render.h"
#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define LINE_THICKNESS 4
#define SPLIT_SDL_COLOR(var) var.r, var.g, var.b, var.a

typedef struct {
    size_t lowestVisibleLine;
    int charWidth;
    int lineHeight;
} RenderState;

static int lineHeight = 0;
static int charWidth = 0;

static void RenderBottomLine(const EditorState *const editor, const SDLState *const sdl, const UserSettings *const settings) {

    SDL_Rect bottomBorder;
    bottomBorder.x = 0;
    bottomBorder.y = sdl->h - lineHeight - LINE_THICKNESS;
    bottomBorder.w = sdl->w;
    bottomBorder.h = LINE_THICKNESS;

    SDL_SetRenderDrawColor(sdl->renderer, SPLIT_SDL_COLOR(settings->lineColor));
    SDL_RenderFillRect(sdl->renderer, &bottomBorder);
}

static void RenderText(const EditorState *const editor, const SDLState *const sdl, const UserSettings *const settings, RenderState *renderState) {

    int remainingHeight = sdl->h;
    int lineCount = remainingHeight / renderState->lineHeight;
    size_t iStart = renderState->lowestVisibleLine == 0 ? 0 : ALI_Get(&editor->newlineIndexes, renderState->lowestVisibleLine);
    size_t iEnd;
    if (lineCount + iStart >= editor->newlineIndexes.contentLength) {
        iEnd = editor->text.contentLength - 1;
    } else {
        iEnd = ALI_Get(&editor->newlineIndexes, renderState->lowestVisibleLine + lineCount);
    }
    size_t renderLen = iEnd - iStart;

    char *renderString;
    if (editor->text.gapIndex >= iStart && editor->text.gapIndex < iEnd) {

        renderLen -= editor->text.gapWidth;
        renderString = malloc(renderLen + 1);
        int iGap = editor->text.gapIndex;
        int iGapBuffer = iStart;
        int iRender = 0;
        while (iGapBuffer < iGap) {
            renderString[iRender] = editor->text.buffer[iGapBuffer];
            iRender++;
            iGapBuffer++;
        }

        iGapBuffer += editor->text.gapWidth;

        while (iGapBuffer < iEnd) {
            renderString[iRender] = editor->text.buffer[iGapBuffer];
            iRender++;
            iGapBuffer++;
        }
    } else {
        renderString = malloc(renderLen + 1);
        memcpy(renderString, editor->text.buffer + iStart, renderLen);
    }

    renderString[renderLen] = '\0';
    for (size_t i = 0; i < renderLen; i++) {
        if (renderString[i] == '\n') {
            renderString[i] = '\0';
        }
    }

    int lineY = 0;
    char *p2 = renderString;
    int i = 0;
    while (p2 < renderString + renderLen) {

        size_t len = strlen(p2);
        if (len != 0) {

            SDL_Surface *ts = TTF_RenderUTF8_Blended(sdl->font, p2, settings->fontColor);
            if (ts == NULL) {
                break;
            }
            SDL_Texture *tt = SDL_CreateTextureFromSurface(sdl->renderer, ts);

            SDL_Rect r;
            r.x = 0;
            r.y = lineY;
            r.h = ts->h;
            r.w = ts->w;

            SDL_RenderCopy(sdl->renderer, tt, NULL, &r);

            SDL_FreeSurface(ts);
            SDL_DestroyTexture(tt);
        }
        lineY += renderState->lineHeight;
        p2 += len + 1;
    }

    free(renderString);
}

static void RenderCursor(const EditorState *const editor, SDLState *sdl, const UserSettings *const settings, RenderState *renderState) {

    SDL_Rect cursor;
    cursor.x = renderState->charWidth * editor->cursor.effectiveCol;
    cursor.y = (editor->cursor.lineIndex - renderState->lowestVisibleLine) * renderState->lineHeight;
    cursor.w = 2;
    cursor.h = renderState->lineHeight;

    SDL_SetRenderDrawColor(sdl->renderer, SPLIT_SDL_COLOR(settings->cursorColor));
    SDL_RenderFillRect(sdl->renderer, &cursor);
}

void Render(const EditorState *const editor, SDLState *sdl, const UserSettings *const settings) {

    static RenderState renderState;

    SDL_SetRenderDrawColor(sdl->renderer, SPLIT_SDL_COLOR(settings->bgColor));
    SDL_RenderClear(sdl->renderer);

    renderState.lineHeight = TTF_FontHeight(sdl->font);
    TTF_SizeUTF8(sdl->font, "0", &renderState.charWidth, NULL);
    renderState.lowestVisibleLine = 0;

    RenderBottomLine(editor, sdl, settings);

    RenderText(editor, sdl, settings, &renderState);
    
    RenderCursor(editor, sdl, settings, &renderState);

    SDL_RenderPresent(sdl->renderer);
}
