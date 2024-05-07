#include "main.h"
#include "input.h"
#include "render.h"
#include "editor.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720
#define DEFAULT_FONT_SIZE 20

void InitSettings(UserSettings *s) {

    s->fontSize = DEFAULT_FONT_SIZE;
    s->fontColor.r = 255;
    s->fontColor.g = 255;
    s->fontColor.b = 255;
    s->fontColor.a = 255;

    s->bgColor.r = 50;
    s->bgColor.g = 50;
    s->bgColor.b = 50;
    s->bgColor.a = 255;

    s->lineColor.r = 120;
    s->lineColor.g = 120;
    s->lineColor.b = 120;
    s->lineColor.a = 255;

    s->cursorColor.r = 200;
    s->cursorColor.g = 200;
    s->cursorColor.b = 200;
    s->cursorColor.a = 120;
}

void SetupSDL(SDLState *sdl, UserSettings *settings) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialize SDL. Error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    const int windowFlags = SDL_WINDOW_RESIZABLE;
    sdl->window = SDL_CreateWindow(
        "JVim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, windowFlags);

    if (!sdl->window) {
        printf("Failed to create window. Error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    const int rendererFlags = SDL_RENDERER_ACCELERATED;
    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, rendererFlags);

    if (!sdl->renderer) {
        printf("Failed to create renderer. Error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND);

    TTF_Init();
    sdl->font =
        TTF_OpenFont("CousineNerdFontMono-Regular.ttf", settings->fontSize);

    sdl->w = DEFAULT_SCREEN_WIDTH;
    sdl->h = DEFAULT_SCREEN_HEIGHT;
    sdl->quit = 0;
}

void InitEditorState(EditorState *e, FILE *f) {

    e->preferredCursorColIndex = 0;
    e->cursorLineIndex = 0;
    e->lowestVisibleLineIndex = 0;
    e->fileLineCount = 0;

    InitGapBufferFromFile(&e->text, f);

    InitArrayListInt(&e->newlineIndices, 128);
}

void InitJvimState(JVIMState* jvs, FILE* file) {

    InitSettings(&jvs->settings);
    InitEditor(&jvs->editor, file);
    SetupSDL(&jvs->sdl, &jvs->settings); 
}

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Invalid Arguments\n");
        exit(EXIT_FAILURE);
    }
    char *filePath = argv[1];
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Cannot open file");
        exit(EXIT_FAILURE);
    }

    JVIMState jvs;
    InitJvimState(&jvs, file);
    
    InitEditor(&jvs.editor, file);



    while (!jvs.sdl.quit) {

        HandleInput(&jvs);

        if (SDL_GetRendererOutputSize(jvs.sdl.renderer, &jvs.sdl.w,
                                      &jvs.sdl.h) != 0) {
            printf("SDL_GetRendererOutputSize failed. Error: %s",
                   SDL_GetError());
            exit(EXIT_FAILURE);
        }

        Render(&jvs);


        SDL_Delay(16);
    }

    CleanupGapBuffer(&jvs.editor.text);
    SDL_Quit();
    TTF_Quit();
    exit(EXIT_SUCCESS);
}
