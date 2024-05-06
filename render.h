#pragma once

typedef struct UserSettings UserSettings;
typedef struct EditorState EditorState;
typedef struct SDLState SDLState;

void Render(SDLState* sdlState, EditorState* editorState, UserSettings* settings);
