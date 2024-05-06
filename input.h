#pragma once

typedef union SDL_Event SDL_Event;
typedef struct SDLState SDLState;
typedef struct EditorState EditorState;

void HandleInput(SDLState* sdlState, EditorState* editorState);

void HandleKeyDown(SDL_Event* inputEvent, EditorState* editorState);

void HandleKeyUp(SDL_Event* inputEvent, EditorState* editorState);
