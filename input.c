#include "input.h"
#include <SDL2/SDL.h>

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
