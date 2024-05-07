#include "input.h"
#include "main.h"
#include <SDL2/SDL.h>

void HandleInput(JVIMState *jvs) {

    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {
        switch (inputEvent.type) {
        case SDL_QUIT:
            jvs->sdl.quit = 1;
            break;
        case SDL_KEYDOWN:
            HandleKeyDown(&inputEvent, &jvs->editor);
            break;
        case SDL_KEYUP:
            HandleKeyUp(&inputEvent, &jvs->editor);
            break;
        default:
            break;
        }
    }
}

void HandleKeyDown(SDL_Event *inputEvent, EditorState *editorState) {

    switch (inputEvent->key.keysym.sym) {
    case SDLK_j:
        printf("j");
        if (editorState->lowestVisibleLineIndex + editorState->cursorLineIndex + 1 <= editorState->fileLineCount) {
            if (editorState->cursorLineIndex + 1 == editorState->visibleLineCount) {
                editorState->lowestVisibleLineIndex++;
            } else {
                editorState->cursorLineIndex++;
            }
        }
        break;
    case SDLK_k:
        printf("k");
        if (editorState->cursorLineIndex > 0) {
            editorState->cursorLineIndex--;
        } else if (editorState->lowestVisibleLineIndex > 0) {
            editorState->lowestVisibleLineIndex--;
        }
        break;
    case SDLK_h:
        printf("h");
        if (editorState->preferredCursorColIndex - 1 >= 0) {
            editorState->preferredCursorColIndex--;
        }
        break;
    case SDLK_l:
        printf("l");
        if (editorState->preferredCursorColIndex + 1 < editorState->cursorLineLength) {
            editorState->preferredCursorColIndex++;
        }
        break;
    }
}

void HandleKeyUp(SDL_Event *inputEvent, EditorState *editorState) {

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
