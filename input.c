#include "input.h"
#include <SDL2/SDL.h>

typedef enum { Normal, Insert } Mode;

static Mode mode = Normal;

static void HandleKeyDown(SDL_Event *inputEvent, EditorState *editor) {

    printf("%c\n", inputEvent->key.keysym.sym);

    switch (inputEvent->key.keysym.sym) {
    case SDLK_j:
        printf("j");
        Editor_MoveCursor(editor, Down, 1);
        break;
    case SDLK_k:
        printf("k");
        Editor_MoveCursor(editor, Up, 1);
        break;
    case SDLK_h:
        printf("h");
        Editor_MoveCursor(editor, Left, 1);
        break;
    case SDLK_l:
        printf("l");
        Editor_MoveCursor(editor, Right, 1);
        break;
    }
}

static void HandleKeyUp(SDL_Event *inputEvent, EditorState *editorState) {

    switch (inputEvent->key.keysym.sym) {
    case SDLK_j:
        printf("j");
        break;
    case SDLK_k:
        printf("k");
        break;
    case SDLK_h:
        printf("h");
        break;
    case SDLK_l:
        printf("l");
        break;
    }
}

void Input_HandleInput(EditorState *editor, SDLState *sdl) {

    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {
        switch (inputEvent.type) {
        case SDL_QUIT:
            sdl->quit = 1;
            break;
        case SDL_KEYDOWN:
            HandleKeyDown(&inputEvent, editor);
            break;
        case SDL_KEYUP:
            HandleKeyUp(&inputEvent, editor);
            break;
        default:
            break;
        }
    }
}
