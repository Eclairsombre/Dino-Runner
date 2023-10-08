
// Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;
#include <string.h>
#include <cstdio>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_video.h"
#include "dino.h"
#include "showScore.h"
#include "start.h"
#include "fileCreateWrite.h"
#include "map.h"

void menu(bool &choix, bool &musique)
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

    int mouseX;
    int mouseY;

    SDL_Color blanc = {255, 255, 255};
    SDL_Color noir = {0, 0, 0};
    TTF_Font *dogica = TTF_OpenFont("font/dogica.ttf", 16);
    if (dogica == NULL)
    {
        fprintf(stderr, "Impossible de charger \"dogica.ttf\"");
        exit(EXIT_FAILURE);
    }

    SDL_Rect bouton_play;
    bouton_play.h = 75;
    bouton_play.w = 200;
    bouton_play.x = 250;
    bouton_play.y = 220;
    SDL_Rect bouton_score;
    bouton_score.h = 75;
    bouton_score.w = 200;
    bouton_score.x = 250;
    bouton_score.y = 300;

    SDL_Rect bouton_settings;
    bouton_settings.h = 75;
    bouton_settings.w = 200;
    bouton_settings.x = 250;
    bouton_settings.y = 380;

    SDL_Surface *texte_play = TTF_RenderText_Blended(dogica, "PLAY", blanc);
    SDL_Surface *texte_dino = TTF_RenderText_Blended(dogica, "DINO RUNNER", noir);
    SDL_Surface *texte_score = TTF_RenderText_Blended(dogica, "SCORE", blanc);
    SDL_Surface *texte_settings = TTF_RenderText_Blended(dogica, "SETTINGS", blanc);
    int txtW = 0;
    int txtH = 0;
    SDL_Texture *pTextureTxtPlay = SDL_CreateTextureFromSurface(rend, texte_play);
    SDL_Texture *pTextureTxtDino = SDL_CreateTextureFromSurface(rend, texte_dino);
    SDL_Texture *pTextureTxtScore = SDL_CreateTextureFromSurface(rend, texte_score);
    SDL_Texture *pTextureTxtSettings = SDL_CreateTextureFromSurface(rend, texte_settings);

    SDL_FreeSurface(texte_dino);
    SDL_FreeSurface(texte_play);
    SDL_FreeSurface(texte_score);
    SDL_FreeSurface(texte_settings);

    SDL_QueryTexture(pTextureTxtPlay, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_play;
    t_play.x = 290;
    t_play.y = 240;
    t_play.w = txtW + 60;
    t_play.h = txtH + 20;
    SDL_QueryTexture(pTextureTxtScore, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_score;
    t_score.x = 280;
    t_score.y = 320;
    t_score.w = txtW + 60;
    t_score.h = txtH + 20;
    SDL_QueryTexture(pTextureTxtSettings, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_settings;
    t_settings.x = 260;
    t_settings.y = 400;
    t_settings.w = txtW + 60;
    t_settings.h = txtH + 20;
    SDL_QueryTexture(pTextureTxtDino, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_dino;
    t_dino.x = 180;
    t_dino.y = 25;
    t_dino.w = txtW + 200;
    t_dino.h = txtH + 30;

    SDL_Rect ligneDino;
    ligneDino.x = 180;
    ligneDino.y = 75;
    ligneDino.w = txtW + 190;
    ligneDino.h = 5;

    SDL_Event event;

    SDL_Rect arrierePlan;
    arrierePlan.x = 0;
    arrierePlan.y = 0;
    arrierePlan.h = 200;
    arrierePlan.w = 700;

    dino d(rend);
    SDL_Rect hitbox;
    hitbox.x = 100;
    hitbox.y = 122;
    hitbox.h = 80;
    hitbox.w = 60;
    d.setHitbox(hitbox);
    d.animationDino();

    while (!stop)

    {
        d.animationDino();

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderFillRect(rend, &arrierePlan);
        SDL_RenderDrawRect(rend, &bouton_play);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &bouton_score);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &bouton_settings);

        SDL_RenderCopy(rend, pTextureTxtPlay, nullptr, &t_play);

        SDL_RenderCopy(rend, pTextureTxtScore, nullptr, &t_score);
        SDL_RenderCopy(rend, pTextureTxtSettings, nullptr, &t_settings);

        SDL_RenderCopy(rend, pTextureTxtDino, nullptr, &t_dino);

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderFillRect(rend, &ligneDino);

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
                    playGame(choix, musique);
                }
            case SDL_MOUSEBUTTONDOWN:
                mouseX = event.button.x;
                mouseY = event.button.y;
                if (mouseX >= 250 && mouseX <= 450 && mouseY >= 220 && mouseY <= 295)
                {
                    stop = true;
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    playGame(choix, musique);
                }
                else if (mouseX >= 250 && mouseX <= 450 && mouseY >= 380 && mouseY <= 455)
                {
                    stop = true;
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    settings(choix, musique);
                }
                else if (mouseX >= 250 && mouseX <= 450 && mouseY >= 300 && mouseY <= 375)
                {
                    stop = true;
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    score(choix, musique);
                }
            }
        }
        d.show(rend);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();
}
void playGame(bool &choix, bool &musique)
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

    if (musique)
    {
        Mix_Music *music;
        music = Mix_LoadMUS("./music/song.mp3");
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(5);
    }

    dino d(rend);
    map m(rend, choix);

    bool stop = false, start = true, restart = false;
    int time = 0;
    int mouseX;
    int mouseY;

    SDL_Event event;

    SDL_Color noir = {0, 0, 0}, blanc = {255, 255, 255};
    TTF_Font *dogica = TTF_OpenFont("font/dogica.ttf", 16);
    if (dogica == NULL)
    {
        fprintf(stderr, "Impossible de charger \"dogica.ttf\"");
        exit(EXIT_FAILURE);
    }
    string text = "SCORE:";

    SDL_Texture *pTextureTxtScore;

    SDL_Rect t_score;

    bool writeScore = true;

    while (!stop)
    {
        if (start && !writeScore)
        {
            if (checkAndCreateFile("./file/score.txt"))
            {
                writeScore = true;

                writeInFile("./file/score.txt", to_string(m.getScore()).c_str());
            }
        }

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                // Quit
                stop = true;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:

                    if (!restart)
                    {
                        start = false;
                    }
                }
            case SDL_MOUSEBUTTONDOWN:
                mouseX = event.button.x;
                mouseY = event.button.y;
                if (restart)
                {
                    if (mouseX >= 400 && mouseX <= 600 && mouseY >= 270 && mouseY <= 320)
                    {
                        dino tempDino(rend);
                        d = tempDino;

                        map tempMap(rend, choix);
                        m = tempMap;

                        restart = false;
                        start = false;
                        writeScore = false;
                    }
                    else if (mouseX >= 400 && mouseX <= 600 && mouseY >= 325 && mouseY <= 375)
                    {
                        stop = true;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_RenderClear(rend);

        d.animationDino();
        if (!restart)
        {
            m.showKey(rend, dogica, noir, choix);
        }

        d.show(rend);

        m.show(rend);

        if (restart)

        {
            m.restartWindow(rend, dogica, blanc);
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);

        time = SDL_GetTicks();

        while (!start)
        {
            if (!restart)
            {
                restart = true;
            }
            if (writeScore)
            {
                writeScore = false;
            }
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

            SDL_RenderClear(rend);

            d.animationDino();

            d.show(rend);

            m.show(rend);

            d.dinoEvent(event, m, start);

            d.Gravity();

            m.addObstacle(rend, time);

            m.UpdateObstacle();

            m.OiseauAnimation();

            m.ActuVitesse(time);
            m.actuScore(rend, time, text, pTextureTxtScore, t_score, dogica, noir);

            d.collision(m, start);

            SDL_RenderPresent(rend);
            SDL_Delay(1000 / 60);
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    Mix_CloseAudio();

    SDL_Quit();
    menu(choix, musique);
}

void settings(bool &choix, bool &musique)
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

    int mouseX;
    int mouseY;

    SDL_Color blanc = {255, 255, 255};
    TTF_Font *dogica = TTF_OpenFont("font/dogica.ttf", 16);
    if (dogica == NULL)
    {
        fprintf(stderr, "Impossible de charger \"dogica.ttf\"");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *texte_settings = TTF_RenderText_Blended(dogica, "SETTINGS", blanc);
    SDL_Surface *texte_back = TTF_RenderText_Blended(dogica, "BACK", blanc);

    int txtW = 0;
    int txtH = 0;

    SDL_Texture *pTextureTxtSettings = SDL_CreateTextureFromSurface(rend, texte_settings);
    SDL_Texture *pTextureTxtBack = SDL_CreateTextureFromSurface(rend, texte_back);
    SDL_Texture *pTextureTxtMode;
    SDL_Texture *pTextureTxtMusic;

    SDL_FreeSurface(texte_settings);

    SDL_FreeSurface(texte_back);

    SDL_QueryTexture(pTextureTxtSettings, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_settings;
    t_settings.x = 235;
    t_settings.y = 50;
    t_settings.w = txtW + 100;
    t_settings.h = txtH + 40;

    SDL_QueryTexture(pTextureTxtBack, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_back;
    t_back.h = txtH + 20;
    t_back.w = txtW + 40;
    t_back.x = 75;
    t_back.y = 420;

    SDL_Rect t_mode;
    SDL_Rect t_music;

    SDL_Rect retour;
    retour.h = 75;
    retour.w = 150;
    retour.x = 50;
    retour.y = 400;

    SDL_Rect mode;
    mode.h = 75;
    mode.w = 390;
    mode.x = 190;
    mode.y = 150;

    SDL_Rect music;
    music.h = 75;
    music.w = 230;
    music.x = 190;
    music.y = 250;

    SDL_Event event;
    while (!stop)

    {

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &retour);

        SDL_RenderDrawRect(rend, &mode);
        SDL_RenderDrawRect(rend, &music);

        SDL_RenderCopy(rend, pTextureTxtSettings, nullptr, &t_settings);
        SDL_RenderCopy(rend, pTextureTxtBack, nullptr, &t_back);

        actuButtonMode(rend, pTextureTxtMode, t_mode, dogica, blanc, choix);
        actuButtonMusic(rend, pTextureTxtMusic, t_music, dogica, blanc, musique);

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                // Quit
                stop = true;

                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseX = event.button.x;
                mouseY = event.button.y;

                if (mouseX >= 50 && mouseX <= 250 && mouseY >= 400 && mouseY <= 475)
                {
                    stop = true;
                }
                else if (mouseX >= 190 && mouseX <= 600 && mouseY >= 150 && mouseY <= 225)
                {

                    if (choix)
                    {
                        choix = false;
                    }
                    else
                    {
                        choix = true;
                    }
                }
                else if (mouseX >= 190 && mouseX <= 420 && mouseY >= 250 && mouseY <= 325)
                {

                    if (musique)
                    {
                        musique = false;
                    }
                    else
                    {
                        musique = true;
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
    menu(choix, musique);
}

void score(bool &choix, bool &musique)
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

    int mouseX;
    int mouseY;

    SDL_Color blanc = {255, 255, 255};
    TTF_Font *dogica = TTF_OpenFont("font/dogica.ttf", 16);
    if (dogica == NULL)
    {
        fprintf(stderr, "Impossible de charger \"dogica.ttf\"");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *texte_score = TTF_RenderText_Blended(dogica, "SCORE", blanc);
    SDL_Surface *texte_back = TTF_RenderText_Blended(dogica, "BACK", blanc);
    SDL_Surface *texte_highscore = TTF_RenderText_Blended(dogica, "HIGHSCORE :", blanc);
    SDL_Surface *texte_lastPlay = TTF_RenderText_Blended(dogica, "LAST 10 GAME :", blanc);

    int txtW = 0;
    int txtH = 0;

    SDL_Texture *pTextureTxtScore = SDL_CreateTextureFromSurface(rend, texte_score);
    SDL_Texture *pTextureTxtBack = SDL_CreateTextureFromSurface(rend, texte_back);
    SDL_Texture *pTextureTxtHighScore = SDL_CreateTextureFromSurface(rend, texte_highscore);
    SDL_Texture *pTextureTxtLastPlay = SDL_CreateTextureFromSurface(rend, texte_lastPlay);

    SDL_FreeSurface(texte_score);
    SDL_FreeSurface(texte_highscore);
    SDL_FreeSurface(texte_back);
    SDL_FreeSurface(texte_lastPlay);

    SDL_QueryTexture(pTextureTxtScore, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_score;
    t_score.x = 240;
    t_score.y = 50;
    t_score.w = txtW + 120;
    t_score.h = txtH + 60;

    SDL_QueryTexture(pTextureTxtHighScore, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_highscore;
    t_highscore.x = 100;
    t_highscore.y = 150;
    t_highscore.w = txtW + 30;
    t_highscore.h = txtH + 10;

    SDL_QueryTexture(pTextureTxtBack, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_back;
    t_back.h = txtH + 20;
    t_back.w = txtW + 40;
    t_back.x = 75;
    t_back.y = 420;

    SDL_QueryTexture(pTextureTxtLastPlay, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_lastPlay;
    t_lastPlay.x = 350;
    t_lastPlay.y = 150;
    t_lastPlay.w = txtW + 30;
    t_lastPlay.h = txtH + 10;

    SDL_Rect retour;
    retour.h = 75;
    retour.w = 150;
    retour.x = 50;
    retour.y = 400;

    SDL_Event event;

    vector<string> lignes = CatchLastLignes("./file/score.txt", 10);
    while (!stop)

    {

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

        SDL_RenderClear(rend);

        showScore(rend, lignes, dogica, blanc);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &retour);

        SDL_RenderCopy(rend, pTextureTxtScore, nullptr, &t_score);
        SDL_RenderCopy(rend, pTextureTxtBack, nullptr, &t_back);
        SDL_RenderCopy(rend, pTextureTxtHighScore, nullptr, &t_highscore);
        SDL_RenderCopy(rend, pTextureTxtLastPlay, nullptr, &t_lastPlay);

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                // Quit
                stop = true;

                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseX = event.button.x;
                mouseY = event.button.y;

                if (mouseX >= 50 && mouseX <= 250 && mouseY >= 400 && mouseY <= 475)
                {
                    stop = true;
                }
                else if (mouseX >= 190 && mouseX <= 600 && mouseY >= 150 && mouseY <= 225)
                {

                    if (choix)
                    {
                        choix = false;
                    }
                    else
                    {
                        choix = true;
                    }
                }
                else if (mouseX >= 190 && mouseX <= 420 && mouseY >= 250 && mouseY <= 325)
                {

                    if (musique)
                    {
                        musique = false;
                    }
                    else
                    {
                        musique = true;
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
    menu(choix, musique);
}