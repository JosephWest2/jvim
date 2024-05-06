#include "arrayList.h"
#include "gapBuffer.h"
#include "input.h"
#include "ui.h"
#include "main.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720
#define DEFAULT_FONT_SIZE 20
#define DEFAULT_LINE_HEIGHT 20


void SetupSDL(SDLState *s) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialize SDL. Error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    const int windowFlags = SDL_WINDOW_RESIZABLE;
    s->window = SDL_CreateWindow("JVim", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH,
                                 DEFAULT_SCREEN_HEIGHT, windowFlags);

    if (!s->window) {
        printf("Failed to create window. Error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    const int rendererFlags = SDL_RENDERER_ACCELERATED;
    s->renderer = SDL_CreateRenderer(s->window, -1, rendererFlags);

    if (!s->renderer) {
        printf("Failed to create renderer. Error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    s->w = DEFAULT_SCREEN_WIDTH;
    s->h = DEFAULT_SCREEN_HEIGHT;
    s->quit = 0;
}

void InitSettings(UserSettings* s) {

    s->fontSize = DEFAULT_FONT_SIZE;
    s->lineHeight = DEFAULT_LINE_HEIGHT;
    s->fontColor.r = 255;
    s->fontColor.g = 255;
    s->fontColor.b = 255;
    s->fontColor.a = 255;

    s->bgColor.r = 50;
    s->bgColor.g = 50;
    s->bgColor.b = 50;
    s->bgColor.a = 255;

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

    UserSettings settings;
    InitSettings(&settings);

    GapBuffer gb;
    InitGapBufferFromFile(&gb, file);
    PrintBuffer(&gb);

    ArrayList newlineIndices;
    InitArrayList(&newlineIndices, 128);

    SDLState sdlState;
    SetupSDL(&sdlState);

    TTF_Init();
    TTF_Font *font =
        TTF_OpenFont("CousineNerdFontMono-Regular.ttf", settings.fontSize);


    while (!sdlState.quit) {

        HandleInput(&sdlState);

        if (SDL_GetRendererOutputSize(sdlState.renderer, &sdlState.w, &sdlState.h) != 0) {
            printf("SDL_GetRendererOutputSize failed. Error: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        SDL_SetRenderDrawBlendMode(sdlState.renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(sdlState.renderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlState.renderer);

        RenderUI(sdlState.renderer, &sdlState.w, &sdlState.h);

        SDL_Color white = {255, 255, 255};

        for (int i = 0; i < gb.contentLength; i++) {
            if (gb.buffer[i] == '\n') {
                printf("%d index\n", i);
            }
        }

        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "T", white);
        SDL_Texture *textTexture =
            SDL_CreateTextureFromSurface(sdlState.renderer, textSurface);
        SDL_Rect Message_rect;
        Message_rect.x = 0;
        Message_rect.y = 0;
        int scalar = settings.lineHeight / textSurface->h;

        Message_rect.w = textSurface->w;
        Message_rect.h = textSurface->h;
        SDL_RenderCopy(sdlState.renderer, textTexture, NULL, &Message_rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(sdlState.renderer);

        SDL_Delay(16);
    }

    CleanupGapBuffer(&gb);
    SDL_Quit();
    TTF_Quit();
    exit(EXIT_SUCCESS);
}
