#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "editor.h"
#include "gapBuffer.h"
#include "arrayListInt.h"
#include "arrayListStr.h"

typedef enum {
    Left,
    Right,
    Up,
    Down,
} Direction2D;

typedef enum {
    left,
    right,
} Direction1D;

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
