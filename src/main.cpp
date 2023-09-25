// Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;
#include <string.h>
#include <cstdio>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_image.h"
#include "player.cpp"
#include "monster.cpp"
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

    player p;
    InitPlayer(p);

    monster m;

    map ma;
    InitMap(ma);

    string direction;
    InitMonster(m);
    bool up = false, down = false, right = false, left = false;
    
    

    SDL_Event event;
    while (!close)
    {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        //DrawMap(ma, rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &p.PlayerRect);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &m.MonsterRect);

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
                case SDL_SCANCODE_LEFT:
                    left = true;
                    break;
                case SDL_SCANCODE_RIGHT:
                    right = true;
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
                    break;
                case SDL_SCANCODE_LEFT:
                    left = false;
                    break;
                case SDL_SCANCODE_RIGHT:
                    right = false;
                    break;
                default:
                    break;
                }
                break;
            }
        }

        if (up == true)
        {
            p.PlayerRect.y -= 3;
        }
        if (down == true)
        {
            p.PlayerRect.y += 3;
        }
        if (right == true)
        {
            p.PlayerRect.x += 3;
        }
        if (left == true)
        {
            p.PlayerRect.x -= 3;
        }

        //MonsterWalk(m, direction);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    Mix_CloseAudio();

    SDL_Quit();
    return 0;
}
