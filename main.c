#include "consts.h"
#include "gapBuffer.h"
#include "input.h"
#include "ui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int Quit(Result status) {
    switch (status) {
    case Success:
        printf("Program exited normally");
        break;
    case Error:
        printf("Program error, terminating");
        break;
    }
    SDL_Quit();
    TTF_Quit();
    exit((int)status);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Invalid Arguments\n");
        Quit(Error);
    }
    char *filePath = argv[1];
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Cannot open file");
        Quit(Error);
    }
    char buffer[255];

    GapBuffer gb;
    InitGapBuffer(&gb);

    while (1) {
        char c = fgetc(file);
        if (feof(file)) {
            break;
        }
        AppendToBuffer(&gb, c);
    }

    PrintBuffer(&gb);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int w = SCREEN_WIDTH;
    int h = SCREEN_HEIGHT;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialize SDL. Error: %s", SDL_GetError());
        Quit(Error);
    }
    const int windowFlags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("JVim", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, windowFlags);
    if (!window) {
        printf("Failed to create window. Error: %s", SDL_GetError());
        Quit(Error);
    }

    const int rendererFlags = SDL_RENDERER_ACCELERATED;
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("CousineNerdFontMono-Regular.ttf", 24);

    // main loop
    int quit = 0;
    while (!quit) {
        SDL_Event inputEvent;
        while (SDL_PollEvent(&inputEvent)) {
            switch (inputEvent.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                printf("keydown");
                HandleKeyDown(&inputEvent);
                break;
            case SDL_KEYUP:
                printf("keyup");
                HandleKeyUp(&inputEvent);
                break;
            default:
                break;
            }
        }

        if (SDL_GetRendererOutputSize(renderer, &w, &h) != 0) {
            printf("SDL_GetDesktopDisplayMode failed");
            Quit(Error);
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        RenderUI(renderer, &w, &h);

        //    RenderText(renderer, &w, &h);
        SDL_Color white = {255, 255, 255};
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Test", white);
        SDL_Texture *textTexture =
            SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect Message_rect;
        Message_rect.x = 0;
        Message_rect.y = 0;
        Message_rect.w = 100;
        Message_rect.h = 100;
        SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    CleanupGapBuffer(&gb);
    Quit(Success);
}
