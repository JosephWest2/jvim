#pragma once
#include <SDL2/SDL_pixels.h>
#include "gapBuffer.h"
#include "arrayList.h"

typedef struct _TTF_Font TTF_Font; 
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Window SDL_Window;

typedef struct UserSettings {
    int fontSize;
    int lineHeight;
    SDL_Color fontColor;
    SDL_Color lineColor;
    SDL_Color bgColor;
    SDL_Color cursorColor;

} UserSettings;

typedef struct EditorState {
    int lowestVisibleLine;
    int cursorLine;
    int cursorRow;
    int totalLines;
    GapBuffer textBuffer;
    ArrayList newlineIndices; 

} EditorState;

typedef struct SDLState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int w;
    int h;
    int quit;

} SDLState;
