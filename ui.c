#include "ui.h"
#include "consts.h"
#include <SDL2/SDL.h>

void RenderUI(SDL_Renderer *const renderer, const int *const screenWidth,
              const int *const screenHeight) {

    SDL_SetRenderDrawColor(renderer, LINE_COLOR);

    SDL_Rect lineNumberBorder;
    lineNumberBorder.x = LEFT_PADDING;
    lineNumberBorder.y = 0;
    lineNumberBorder.h = *screenHeight - BOTTOM_PADDING;
    lineNumberBorder.w = LINE_THICKNESS;

    SDL_Rect bottomBorder;
    bottomBorder.x = LEFT_PADDING;
    bottomBorder.y = *screenHeight - BOTTOM_PADDING;
    bottomBorder.w = *screenWidth - LEFT_PADDING;
    bottomBorder.h = LINE_THICKNESS;

    SDL_Rect rects[] = {lineNumberBorder, bottomBorder};

    SDL_RenderFillRects(renderer, rects, sizeof(rects) / sizeof(SDL_Rect));
}
