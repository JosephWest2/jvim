#include "arrayList.h"
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
#define DEFAULT_FONT_SIZE 20
#define DEFAULT_LINE_HEIGHT 20
#define DEFAULT_CHAR_WIDTH 0.6 * DEFAULT_FONT_SIZE
#define LEFT_PADDING 0
#define BOTTOM_PADDING 0 

typedef struct {
    int fontSize;
    int lineHeight;
    int charWidth;

} UserSettings;

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

    UserSettings settings;
    settings.fontSize = DEFAULT_FONT_SIZE;
    settings.lineHeight = DEFAULT_LINE_HEIGHT;
    settings.charWidth = DEFAULT_CHAR_WIDTH;

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
    ArrayList newlineIndices;
    InitArrayList(&newlineIndices, 128);

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
    TTF_Font *font =
        TTF_OpenFont("CousineNerdFontMono-Regular.ttf", settings.fontSize);
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
        int lineCount = h - BOTTOM_PADDING;
        int maxLineWidth = w - LEFT_PADDING;
        int maxLineChars = maxLineWidth / settings.charWidth;

        for (int i = 0; i < gb.contentLength; i++) {
            if (gb.buffer[i] == '\n') {
                printf("%d index\n", i);
            }

        }


        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "T", white);
        SDL_Texture *textTexture =
            SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect Message_rect;
        Message_rect.x = 0;
        Message_rect.y = 0;
        int scalar = settings.lineHeight / textSurface->h;

        Message_rect.w = textSurface->w;
        Message_rect.h = textSurface->h;
        printf("%d w, %d h\n", textSurface->w, textSurface->h);
        SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    CleanupGapBuffer(&gb);
    Quit(Success);
}
