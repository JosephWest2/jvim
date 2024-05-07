#pragma once

typedef union SDL_Event SDL_Event;
typedef struct SDLState SDLState;
typedef struct EditorState EditorState;
typedef struct JVIMState JVIMState;

void HandleInput(JVIMState* jvs);

void HandleKeyDown(SDL_Event* inputEvent, EditorState* editorState);

void HandleKeyUp(SDL_Event* inputEvent, EditorState* editorState);
