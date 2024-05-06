#include <SDL2/SDL.h>

typedef struct UserSettings {
    int fontSize;
    int lineHeight;
    SDL_Color fontColor;
    SDL_Color bgColor;

} UserSettings;

typedef struct SDLState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int w;
    int h;
    int quit;

} SDLState;
