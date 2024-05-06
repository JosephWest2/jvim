#pragma once

typedef union SDL_Event SDL_Event;
typedef struct SDLState SDLState;

void HandleInput(SDLState* sdlState);

void HandleKeyDown(SDL_Event* inputEvent);

void HandleKeyUp(SDL_Event* inputEvent);
