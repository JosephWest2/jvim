#include "input.h"
#include <SDL2/SDL.h>

typedef enum { Normal, Insert } Mode;

static Mode mode = Normal;

static void HandleKeyDown(SDL_Event *inputEvent, EditorState *editor) {

    int s;

    switch (mode) {

    case Normal:
        switch (inputEvent->key.keysym.sym) {
        case SDLK_j:
            s = editor->text.gapIndex + editor->text.gapWidth;
            for (int i = s; i < editor->text.contentLength; i++) {
                if (editor->text.buffer[i] == '\n') {
                    printf("i: %d\n", i);
                    Editor_MoveCursor(editor, i - s + 1);
                    break;
                }
            }
            break;
        case SDLK_k:
            s = editor->text.gapIndex;
            for (int i = s; i >= 0; i--) {
                if (editor->text.buffer[i] == '\n') {
                    printf("i: %d\n", i);
                    Editor_MoveCursor(editor, i - s);
                    break;
                }
            }
            break;
        case SDLK_h:
            Editor_MoveCursor(editor, -1);
            break;
        case SDLK_l:
            Editor_MoveCursor(editor, 1);
            break;
        case SDLK_i:
            mode = Insert;
            break;
        }

    case Insert:
        switch (inputEvent->key.keysym.sym) {
        case SDLK_ESCAPE:
            mode = Normal;
            break;
        }
    }
}

static void HandleKeyUp(SDL_Event *inputEvent, EditorState *editorState) {

    switch (inputEvent->key.keysym.sym) {
    case SDLK_j:
        break;
    case SDLK_k:
        break;
    case SDLK_h:
        break;
    case SDLK_l:
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
