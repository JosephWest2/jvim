#include "input.h"
#include "main.h"

void HandleInput(SDLState* sdlState) {

    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {
        switch (inputEvent.type) {
        case SDL_QUIT:
            sdlState->quit = 1;
            break;
        case SDL_KEYDOWN:
            HandleKeyDown(&inputEvent);
            break;
        case SDL_KEYUP:
            HandleKeyUp(&inputEvent);
            break;
        default:
            break;
        }
    }
}

void HandleKeyDown(SDL_Event *inputEvent) {

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

void HandleKeyUp(SDL_Event *inputEvent) {

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
