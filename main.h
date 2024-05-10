#pragma once

#include "arrayListInt.h"
#include "arrayListStr.h"
#include "editor.h"
#include "gapBuffer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct UserSettings {
    int fontSize;
    SDL_Color fontColor;
    SDL_Color lineColor;
    SDL_Color bgColor;
    SDL_Color cursorColor;
} UserSettings;

typedef struct SDLState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int w;
    int h;
    int quit;
} SDLState;

typedef struct JVIMState {
    UserSettings settings;
    EditorState editor;
    SDLState sdl;
} JVIMState;
