#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define LINE_THICKNESS 4
#define SPLIT_SDL_COLOR(var) var.r, var.g, var.b, var.a

void RenderBottomLine(SDLState *sdlState, EditorState *editorState,
                      UserSettings *settings, int textLineHeight) {

    SDL_Rect bottomBorder;
    bottomBorder.x = 0;
    bottomBorder.y = sdlState->h - textLineHeight - LINE_THICKNESS;
    bottomBorder.w = sdlState->w;
    bottomBorder.h = LINE_THICKNESS;

    SDL_SetRenderDrawColor(sdlState->renderer,
                           SPLIT_SDL_COLOR(settings->lineColor));
    SDL_RenderFillRect(sdlState->renderer, &bottomBorder);
}

void RenderText(SDLState *sdlState, EditorState *editorState,
                UserSettings *settings, int textLineHeight, int leftPadding) {

    const int remainingHeight = sdlState->h - textLineHeight - LINE_THICKNESS;
    const int lineCount = remainingHeight / textLineHeight;

    int lineY = 0;
    int i = editorState->lowestVisibleLine;
    while (i < lineCount && i < editorState->totalLines) {
        const int lineStart = ALGet(&editorState->newlineIndices, i) + 1;
        int lineEnd;
        if (i == editorState->newlineIndices.contentLength) {
            lineEnd = editorState->textBuffer.contentLength - 1;
        } else {
            lineEnd = ALGet(&editorState->newlineIndices, i + 1);
        }
        char *s = " ";
        int alloc = 0;
        if (lineEnd != lineStart) {
            alloc = 1;
            s = malloc(lineEnd - lineStart + 1);
            memcpy(s, &editorState->textBuffer.buffer[lineStart],
                   lineEnd - lineStart + 1);
            s[lineEnd - lineStart] = '\0';
        }
        SDL_Surface *ts =
            TTF_RenderUTF8_Blended(sdlState->font, s, settings->fontColor);
        SDL_Texture *tt = SDL_CreateTextureFromSurface(sdlState->renderer, ts);
        SDL_Rect r;
        r.x = leftPadding;
        r.y = lineY;
        r.h = ts->h;
        r.w = ts->w;

        SDL_RenderCopy(sdlState->renderer, tt, NULL, &r);

        if (alloc) {
            free(s);
        }
        SDL_FreeSurface(ts);
        SDL_DestroyTexture(tt);

        i++;
        lineY += textLineHeight;
    }
}

void RenderCursor(SDLState* sdlState, EditorState* editorState, UserSettings* settings, int textLineHeight, int leftPadding) {

    int charWidth;
    TTF_SizeUTF8(sdlState->font, "0", &charWidth, NULL); 

    SDL_Rect cursor;
    cursor.x = leftPadding + charWidth * editorState->cursorRow;
    cursor.y = editorState->cursorLine * textLineHeight;
    cursor.w = charWidth;
    cursor.h = textLineHeight;

    SDL_SetRenderDrawColor(sdlState->renderer, SPLIT_SDL_COLOR(settings->cursorColor)); 
    SDL_RenderFillRect(sdlState->renderer, &cursor);

}

void Render(SDLState *sdlState, EditorState *editorState,
            UserSettings *settings) {

    SDL_SetRenderDrawColor(sdlState->renderer,
                           SPLIT_SDL_COLOR(settings->bgColor));
    SDL_RenderClear(sdlState->renderer);

    int textLineHeight = TTF_FontHeight(sdlState->font);
    int leftPadding;

    TTF_SizeUTF8(sdlState->font, "0000.", &leftPadding, NULL);

    RenderBottomLine(sdlState, editorState, settings, textLineHeight);

    RenderText(sdlState, editorState, settings, textLineHeight, leftPadding);

    RenderCursor(sdlState, editorState, settings, textLineHeight, leftPadding);
}
