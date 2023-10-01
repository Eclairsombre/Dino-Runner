

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;
#include <string.h>
#include <cstdio>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_image.h"
#include "dino.cpp"

void playGame(bool &choix);

void menu()
{

    srand(time(NULL));
    // Initialisation
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
    }

    // Initialisation window

    SDL_Window *win = SDL_CreateWindow("DINO RUNNER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    bool stop = false;

    bool choix = true;

    SDL_Event event;
    while (!stop)

    {

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_RenderClear(rend);

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                // Quit
                stop = true;

                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    stop = true;
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    playGame(choix);

                case SDL_SCANCODE_LEFT:
                    cout << choix << endl;
                    if (choix)
                    {
                        choix = false;
                    }
                    else
                    {
                        choix = true;
                    }
                }
            }
        }
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();
}
void playGame(bool &choix)
{

    srand(time(NULL));
    // Initialisation
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
    }

    // Initialisation window

    SDL_Window *win = SDL_CreateWindow("DINO RUNNER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    dino d(rend);

    map m(rend, choix);

    bool stop = false;

    SDL_Event event;

        cout << m.getMode() << endl;

    while (!stop)
    {

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_RenderClear(rend);

        d.chooseClip();

        d.show(rend);

        m.show(rend);

        d.moveDino(event, m, stop);

        d.Gravity();

        m.addObstacle(rend);

        m.moveObstacle();

        m.chooseClip();

        // d.collision(m);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    Mix_CloseAudio();

    SDL_Quit();
    menu();
}
