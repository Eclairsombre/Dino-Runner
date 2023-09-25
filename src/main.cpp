// Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;
#include <string.h>
#include <cstdio>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_image.h"
#include "dino.cpp"
#include "map.cpp"

int main()
{

    srand(time(NULL));
    // Initialisation
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    // Initialisation window

    SDL_Window *win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    bool close = false;
    bool up = false, down = false, space = false;

    dino d;
    InitialiseDino(d);

    map m;
    initialiseMap(m);
    SDL_Event event;
    while (!close)
    {

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderFillRect(rend, &d.hitbox);

        afficherMap(m, rend);

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                // Quit
                close = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    up = true;
                    break;
                case SDL_SCANCODE_DOWN:
                    down = true;
                    break;
                case SDL_SCANCODE_SPACE:
                    space = true;
                    break;

                default:
                    break;
                }
                break;
            }
        }
        if (up == true)
        {
            d.hitbox.y -= 3;
        }
        if (down == true)
        {
            d.hitbox.y += 3;
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    Mix_CloseAudio();

    SDL_Quit();
    return 0;
}
