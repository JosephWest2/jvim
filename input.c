#include "input.h"
#include "main.h"
#include <SDL2/SDL.h>

void HandleInput(SDLState* sdlState, EditorState* editorState) {

    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {
        switch (inputEvent.type) {
        case SDL_QUIT:
            sdlState->quit = 1;
            break;
        case SDL_KEYDOWN:
            HandleKeyDown(&inputEvent, editorState);
            break;
        case SDL_KEYUP:
            HandleKeyUp(&inputEvent, editorState);
            break;
        default:
            break;
        }
    }
}

void HandleKeyDown(SDL_Event *inputEvent, EditorState* editorState) {

    switch (inputEvent->key.keysym.sym) {
    case SDLK_j:
        printf("j");
        if (editorState->cursorLine + 1 < editorState->totalLines) {
            editorState->cursorLine++;
        }
        break;
    case SDLK_k:
        printf("k");
        if (editorState->cursorLine - 1 >= 0) {
            editorState->cursorLine--;
        }
        break;
    case SDLK_h:
        printf("h");
        break;
    case SDLK_l:
        printf("l");
        break;
    }
}

void HandleKeyUp(SDL_Event *inputEvent, EditorState* editorState) {

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
