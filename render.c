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

static char *CreateRenderString(const EditorState *const editor, size_t iStart, size_t iEnd) {

    size_t len = CONTAINS_INCLUSIVE(iStart, iEnd - 1, editor->text.gapIndex) ? iEnd - iStart : iEnd - iStart - editor->text.gapWidth;
    char *out = malloc(len + 1);
    out[len] = '\0';

    int iGap = editor->text.gapIndex;
    int iGapBuffer = iStart;
    int iOut = 0;
    while (iGapBuffer < iGap) {
        out[iOut] = editor->text.buffer[iGapBuffer];
        iOut++;
        iGapBuffer++;
    }

    iGapBuffer += editor->text.gapWidth;

    while (iGapBuffer < iEnd) {
        out[iOut] = editor->text.buffer[iGapBuffer];
        iOut++;
        iGapBuffer++;
    }

    return out;
}

static char *CreateRenderStringRaw(const EditorState *const editor, size_t iStart, size_t iEnd) {

    size_t len = iEnd = iStart;
    char *out = malloc(len + 1);
    out[len] = '\0';
    memcpy(out, editor->text.buffer + iStart, len);
    return out;
}

static void RenderText(char *s, SDLState *sdl, const UserSettings *const settings) {

    SDL_Surface *ts = TTF_RenderUTF8_Blended_Wrapped(sdl->font, s, settings->fontColor, 0);
    if (ts == NULL) {
        return;
    }
    SDL_Texture *tt = SDL_CreateTextureFromSurface(sdl->renderer, ts);

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.h = ts->h;
    r.w = ts->w;

    SDL_RenderCopy(sdl->renderer, tt, NULL, &r);

    SDL_FreeSurface(ts);
    SDL_DestroyTexture(tt);
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

    size_t iStart = renderState.lowestVisibleLine == 0 ? 0 : ALI_Get(&editor->newlineIndexes, renderState.lowestVisibleLine);
    size_t iEnd;
    int remainingHeight = sdl->h - 2 * renderState.lineHeight;
    int lineCount = remainingHeight / renderState.lineHeight;
    if (lineCount + iStart >= editor->newlineIndexes.contentLength) {
        iEnd = editor->text.contentLength - 1;
    } else {
        iEnd = ALI_Get(&editor->newlineIndexes, renderState.lowestVisibleLine + lineCount);
    }

    char * renderString = CreateRenderStringRaw(editor, iStart, iEnd);
    renderString = editor->text.buffer;
    RenderText(renderString, sdl, settings);

    // RenderCursor(editor, sdl, settings, &renderState);

    SDL_RenderPresent(sdl->renderer);
}
