#pragma once

typedef union SDL_Event SDL_Event;

void HandleKeyDown(SDL_Event* inputEvent);

void HandleKeyUp(SDL_Event* inputEvent);
