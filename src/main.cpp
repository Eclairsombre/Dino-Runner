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
    bool up = false, down = false, space = false, temp = false;

    int x = 0;
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
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    up = false;
                    break;
                case SDL_SCANCODE_DOWN:
                    down = false;
                    d.hitbox.h = 60;
                    if (d.sens.compare("haut") == 0)
                    {
                        d.hitbox.y -= 30;
                        temp = false;
                    }
                    break;

                default:
                    break;
                }
                break;
            }
        }
        if (up == true && space == false)
        {
            if (d.sens.compare("haut") == 0)
            {
                d.sens = "bas";
                d.hitbox.y += 160;
                up = false;
            }
            else if (d.sens.compare("bas") == 0)
            {
                d.sens = "haut";
                d.hitbox.y -= 160;
                up = false;
            }
        }
        if (down == true)
        {

            if (d.sens.compare("haut") == 0 && temp == false)
            {
                if (space == false)

                {
                    d.hitbox.h = 30;
                    d.hitbox.y += 30;
                    temp = true;
                }
                else
                {
                    d.hitbox.h = 30;
                    d.hitbox.y = 470;
                    temp = true;
                    space = false;
                    x = 0;
                }
            }
            else if (d.sens.compare("bas") == 0)
            {
                if (space == false)
                {
                    d.hitbox.h = 30;
                }
                else
                {
                    d.hitbox.h = 30;
                    d.hitbox.y = 600;
                    space = false;
                    x = 0;
                }
            }
        }

        if (space == true)
        {
            if (x <= 180)
            {
                jump(d, x);
                x += 5;
            }
            else
            {
                space = false;
                x = 0;
            }
        }
        gravity(d, space);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    Mix_CloseAudio();

    SDL_Quit();
    return 0;
}
