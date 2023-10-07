#include "map.h"
#include <iostream>

#include "SDL2/SDL_image.h"
using namespace std;

void supCaseTab(int i, int &indice, cactus cac[500], oiseau oi[500], nuage nu[500], doubleCactus douCac[500])
{

    if (cac != NULL)
    {
        for (int y = i; y <= indice; y++)
        {
            cac[y] = cac[y + 1];
        }
    }
    if (oi != NULL)
    {
        for (int y = i; y <= indice; y++)
        {
            oi[y] = oi[y + 1];
        }
    }
    if (nu != NULL)
    {
        for (int y = i; y <= indice; y++)
        {
            nu[y] = nu[y + 1];
        }
    }
    if (douCac != NULL)
    {
        for (int y = i; y <= indice; y++)
        {
            douCac[y] = douCac[y + 1];
        }
    }
}

// Set clips for obstacles
void oiseau::set_clips()
{

    if (!inverse)
    {
        this->hitbox.h = 60;
        this->hitbox.w = 60;
        this->hitbox.x = 1020;
        this->hitbox.y = 370;

        this->clip1.x = 87;
        this->clip1.y = 5;
        this->clip1.w = 94;
        this->clip1.h = 77;

        this->clip2.x = 180;
        this->clip2.y = 0;
        this->clip2.w = 95;
        this->clip2.h = 64;
    }
    else
    {
        this->hitbox.h = 60;
        this->hitbox.w = 60;
        this->hitbox.x = 1320;
        this->hitbox.y = 620;

        this->clip1.x = 87;
        this->clip1.y = 25;
        this->clip1.w = 93;
        this->clip1.h = 80;

        this->clip2.x = 180;
        this->clip2.y = 25;
        this->clip2.w = 94;
        this->clip2.h = 82;
    }

    this->clipActuel = this->clip1;
}

void nuage::set_clips()
{

    if (!inverse)
    {
        this->hitbox.h = 30;
        this->hitbox.w = 90;
        this->hitbox.x = 1100;
        this->hitbox.y = 60 + rand() % 200;

        this->clipActuel.x = 0;
        this->clipActuel.y = 0;
        this->clipActuel.w = 90;
        this->clipActuel.h = 30;
    }
    else
    {
        this->hitbox.h = 30;
        this->hitbox.w = 90;
        this->hitbox.x = 1100;
        this->hitbox.y = 900 - rand() % 200;

        this->clipActuel.x = 0;
        this->clipActuel.y = 75;
        this->clipActuel.w = 90;
        this->clipActuel.h = 30;
    }
}

void cactus::set_clipsCactus()
{
    if (!inverse)
    {
        for (int i = 0; i <= 5; i++)
        {
            this->chooseClip[i].h = 73;
            this->chooseClip[i].w = 35;
            this->chooseClip[i].x = 272 + i * 35;
            this->chooseClip[i].y = 0;
        }

        this->hitbox.h = 60;
        this->hitbox.w = 20;
        this->hitbox.x = 1020;
        this->hitbox.y = 440;

        int nb = rand() % 5;
        this->clipActuel = this->chooseClip[nb];
    }
    else
    {
        for (int i = 0; i <= 5; i++)
        {
            this->chooseClip[i].h = 73;
            this->chooseClip[i].w = 35;
            this->chooseClip[i].x = 272 + i * 35;
            this->chooseClip[i].y = 33;
        }

        this->hitbox.h = 60;
        this->hitbox.w = 20;
        this->hitbox.x = 1320;
        this->hitbox.y = 550;

        int nb = rand() % 5;
        this->clipActuel = this->chooseClip[nb];
    }
}

void doubleCactus::set_clipsDoubleCactus()
{
    if (!inverse)
    {
        chooseClip[0].h = 100;
        chooseClip[0].w = 102;
        chooseClip[0].x = 479;
        chooseClip[0].y = 0;

        chooseClip[1].h = 100;
        chooseClip[1].w = 99;
        chooseClip[1].x = 580;
        chooseClip[1].y = 0;

        chooseClip[2].h = 100;
        chooseClip[2].w = 104;
        chooseClip[2].x = 679;
        chooseClip[2].y = 0;

        this->hitbox.h = 60;
        this->hitbox.w = 50;
        this->hitbox.x = 1020;
        this->hitbox.y = 440;

        int nb = rand() % 3;
        this->clipActuel = this->chooseClip[nb];
    }
    else
    {
        chooseClip[0].h = 100;
        chooseClip[0].w = 102;
        chooseClip[0].x = 479;
        chooseClip[0].y = 8;

        chooseClip[1].h = 100;
        chooseClip[1].w = 99;
        chooseClip[1].x = 580;
        chooseClip[1].y = 8;

        chooseClip[2].h = 100;
        chooseClip[2].w = 104;
        chooseClip[2].x = 679;
        chooseClip[2].y = 8;

        this->hitbox.h = 60;
        this->hitbox.w = 50;
        this->hitbox.x = 1320;
        this->hitbox.y = 550;

        int nb = rand() % 3;
        this->clipActuel = this->chooseClip[nb];
    }
}

// Map constructor
map::map(SDL_Renderer *rend, bool choix)
{
    SDL_Rect s;
    this->mode1 = choix;

    if (this->mode1)
    {
        s.h = 600;
        s.w = 1000;
        s.x = 0;
        s.y = 495;
    }
    else if (!this->mode1)
    {

        s.h = 60;
        s.w = 1000;
        s.x = 0;
        s.y = 495;
    }

    this->murUp.x = 1050;
    this->murUp.y = 400;
    this->murUp.w = 2000;
    this->murUp.h = 95;

    this->murDown.x = 1050;
    this->murDown.y = 550;
    this->murDown.w = 2000;
    this->murDown.h = 95;

    this->spawnRate = 4;
    this->sol = s;

    this->close = false;
    this->vx = 4;

    SDL_Surface *imageSurface = IMG_Load("./picture/sprite.png");

    this->imageOiseau = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("./picture/spriteInverse.png");

    this->imageOiseauInverse = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);
}

// Map destructor
map::~map()
{
}

// Animation
void map::OiseauAnimation()
{
    for (int i = 0; i < this->indiceOiseau; i++)
    {
        if (this->oi[i].animation == 1)
        {
            this->oi[i].clipActuel = this->oi[i].clip1;
            this->oi[i].animation += 1;
        }
        else if (this->oi[i].animation == 15)
        {
            this->oi[i].clipActuel = this->oi[i].clip2;
            this->oi[i].animation += 1;
        }
        else if (this->oi[i].animation == 30)
        {
            this->oi[i].clipActuel = this->oi[i].clip2;
            this->oi[i].animation = 1;
        }
        else
        {
            this->oi[i].animation += 1;
        }
    }
}

// Get functions
bool map::getClose()
{
    return this->close;
}
int map::getIndiceCactus()
{
    return this->indiceCactus;
}

bool map::getMode()
{
    return this->mode1;
}

bool map::getSpawnMur()
{
    return this->mUp || this->mDown;
}
SDL_Rect map::getMur()
{
    return this->mur;
}

int map::getScore()
{
    return this->score;
}
int map::getIndiceOiseau()
{
    return this->indiceOiseau;
}

cactus *map::getCactus()
{
    return this->cac;
}

int map::getIndiceDoubleCactus()
{
    return this->indiceCactusDouble;
}

doubleCactus *map::getDoubleCactus()
{
    return this->douCac;
}

oiseau *map::getOiseau()
{
    return this->oi;
}

// Set functions
void map::setMode(bool choix)
{

    this->mode1 = choix;
}
void map::setClose()
{
    this->close = true;
}

// Add random obstacles
void map::addObstacle(SDL_Renderer *rend, int time)
{
    this->timer = SDL_GetTicks();

    if ((this->timer / 1000 - time / 1000) % this->spawnRate == 0 && this->spawn)
    {
        this->spawn = false;

        int nb = rand() % 3;
        int nbInverse = rand() % 3;
        oiseau o;
        o.set_clips();
        cactus c;
        c.set_clipsCactus();
        doubleCactus cd;
        cd.set_clipsDoubleCactus();

        oiseau o2;
        o2.inverse = true;
        o2.set_clips();
        cactus c2;
        c2.inverse = true;
        c2.set_clipsCactus();
        doubleCactus cd2;
        cd2.inverse = true;
        cd2.set_clipsDoubleCactus();

        if (!mUp)
        {
            switch (nb)
            {
            case 0:

                this->oi[this->indiceOiseau] = o;
                this->indiceOiseau += 1;

                break;

            case 1:

                this->cac[this->indiceCactus] = c;
                this->indiceCactus += 1;
                break;
            case 2:

                this->douCac[this->indiceCactusDouble] = cd;
                this->indiceCactusDouble += 1;
                break;

            default:
                break;
            }
        }
        if (!this->mode1 && !mDown)
        {
            switch (nbInverse)
            {
            case 0:

                this->oi[this->indiceOiseau] = o2;
                this->indiceOiseau += 1;

                break;

            case 1:

                this->cac[this->indiceCactus] = c2;
                this->indiceCactus += 1;
                break;

            case 2:

                this->douCac[this->indiceCactusDouble] = cd2;
                this->indiceCactusDouble += 1;
                break;
            default:
                break;
            }
        }
    }
    if ((this->timer / 1000 - time / 1000) % 25 == 0 && (this->timer / 1000 - time / 1000) != 0 && !this->spawnMur && !this->mode1)
    {

        int temp = rand() % 2;
        switch (temp)
        {
        case 0:
            this->mUp = true;
            this->spawnMur = true;
            this->mur = this->murUp;
            break;
        case 1:
            this->mDown = true;
            this->spawnMur = true;
            this->mur = this->murDown;
            break;
        default:
            break;
        }
    }
    if ((this->timer / 1000 - time / 1000) % 25 != 0)
    {
        this->spawnMur = false;
    }
    if ((this->timer / 1000 - time / 1000) % this->spawnRate != 0 && (this->timer / 1000 - time / 1000) % 2 != 0 && this->spawn == false)
    {
        this->spawn = true;
    }

    if ((this->timer / 1000 - time / 1000) % 2 == 0 && this->spawn)
    {
        this->spawn = false;

        nuage n, n2;
        n.set_clips();
        n2.inverse = true;
        n2.set_clips();
        this->nu[this->indiceNuage] = n;
        this->indiceNuage += 1;
        this->nu[this->indiceNuage] = n2;
        this->indiceNuage += 1;
    }
}

void map::UpdateObstacle()
{

    for (int i = 0; i < this->indiceCactus; i++)
    {

        this->cac[i].hitbox.x -= this->vx;

        if (this->cac[i].hitbox.x < -50)
        {
            supCaseTab(i, this->indiceCactus, this->cac, NULL, NULL, NULL);
            indiceCactus -= 1;
        }
    }

    for (int i = 0; i < this->indiceOiseau; i++)
    {

        this->oi[i].hitbox.x -= this->vx;

        if (this->oi[i].hitbox.x < -50)
        {
            supCaseTab(i, this->indiceOiseau, NULL, this->oi, NULL, NULL);
            indiceOiseau -= 1;
        }
    }
    for (int i = 0; i < this->indiceNuage; i++)
    {

        this->nu[i].hitbox.x -= this->vx;

        if (this->nu[i].hitbox.x < -150)
        {

            supCaseTab(i, this->indiceNuage, NULL, NULL, this->nu, NULL);
            indiceNuage -= 1;
        }
    }
    for (int i = 0; i < this->indiceCactusDouble; i++)
    {

        this->douCac[i].hitbox.x -= this->vx;

        if (this->douCac[i].hitbox.x < -150)
        {
            supCaseTab(i, this->indiceCactusDouble, NULL, NULL, NULL, this->douCac);
            indiceCactusDouble -= 1;
        }
    }
    if (this->mUp || this->mDown)
    {

        this->mur.x -= this->vx;
        if (this->mur.x < -2020)
        {
            mUp = false;
            mDown = false;
        }
    }
}

// Show map and obstacles
void map::show(SDL_Renderer *rend)
{

    for (int i = 0; i < this->indiceCactus; i++)
    {

        if (!cac[i].inverse)
        {
            SDL_RenderCopy(rend, this->imageOiseau, &this->cac[i].clipActuel, &this->cac[i].hitbox);
        }
        else
        {
            SDL_RenderCopy(rend, this->imageOiseauInverse, &this->cac[i].clipActuel, &this->cac[i].hitbox);
        }
    }
    for (int i = 0; i < this->indiceOiseau; i++)
    {
        if (!oi[i].inverse)
        {
            SDL_RenderCopy(rend, this->imageOiseau, &this->oi[i].clipActuel, &this->oi[i].hitbox);
        }
        else
        {
            SDL_RenderCopy(rend, this->imageOiseauInverse, &this->oi[i].clipActuel, &this->oi[i].hitbox);
        }
    }
    for (int i = 0; i < this->indiceNuage; i++)
    {
        if (!nu[i].inverse)
        {
            SDL_RenderCopy(rend, this->imageOiseau, &this->nu[i].clipActuel, &this->nu[i].hitbox);
        }
        else
        {
            SDL_RenderCopy(rend, this->imageOiseauInverse, &this->nu[i].clipActuel, &this->nu[i].hitbox);
        }
    }
    for (int i = 0; i < this->indiceCactusDouble; i++)
    {
        if (!douCac[i].inverse)
        {
            SDL_RenderCopy(rend, this->imageOiseau, &this->douCac[i].clipActuel, &this->douCac[i].hitbox);
        }
        else
        {
            SDL_RenderCopy(rend, this->imageOiseauInverse, &this->douCac[i].clipActuel, &this->douCac[i].hitbox);
        }
    }
    if (mUp || mDown)
    {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderFillRect(rend, &this->mur);
    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &this->sol);
}

// Increase speed and spawn rate
void map::ActuVitesse(int time)
{
    this->timer = SDL_GetTicks();
    if ((this->timer / 1000 - time / 1000) == 60)
    {
        this->vx = 5;
        this->spawnRate = 2;

        this->increaseSpeed = false;
    }
    else if ((this->timer / 1000 - time / 1000) % 60 == 0 && (this->timer / 1000 - time / 1000) != 0 && this->increaseSpeed)
    {
        this->increaseSpeed = false;

        this->vx = 5 + (timer / 1000 - time / 1000) / 60 - 1;
    }
    else
    {
        this->increaseSpeed = true;
    }
}

// Update Score while game play
void map::actuScore(SDL_Renderer *rend, int time, string text, SDL_Texture *pTextureTxtScore, SDL_Rect t_score, TTF_Font *dogica, SDL_Color noir)
{
    long timer = SDL_GetTicks();
    this->score = timer / 100 - time / 100;

    text += to_string(this->score);
    const char *textScore = text.c_str();

    SDL_Surface *texte_score = TTF_RenderText_Blended(dogica, textScore, noir);

    int txtW = 0;
    int txtH = 0;

    pTextureTxtScore = SDL_CreateTextureFromSurface(rend, texte_score);
    SDL_FreeSurface(texte_score);
    SDL_QueryTexture(pTextureTxtScore, NULL, NULL, &txtW, &txtH);

    t_score.x = 10;
    t_score.y = 10;
    t_score.w = txtW;
    t_score.h = txtH;

    SDL_RenderCopy(rend, pTextureTxtScore, nullptr, &t_score);
}

// Show key at the start of the game
void map::showKey(SDL_Renderer *rend, TTF_Font *dogica, SDL_Color noir, bool &choix)
{
    SDL_Surface *texte_space = TTF_RenderText_Blended(dogica, "SPACE", noir);
    SDL_Surface *texte_start = TTF_RenderText_Blended(dogica, "JUMP/START", noir);
    SDL_Surface *texte_sneak = TTF_RenderText_Blended(dogica, "SNEAK", noir);
    SDL_Surface *texte_reverse = TTF_RenderText_Blended(dogica, "REVERSE", noir);

    int txtW = 0;
    int txtH = 0;

    SDL_Texture *pTextureTxtScore = SDL_CreateTextureFromSurface(rend, texte_space);
    SDL_FreeSurface(texte_space);

    SDL_Texture *pTextureTxtstart = SDL_CreateTextureFromSurface(rend, texte_start);
    SDL_FreeSurface(texte_start);

    SDL_Texture *pTextureTxtsneak = SDL_CreateTextureFromSurface(rend, texte_sneak);
    SDL_FreeSurface(texte_sneak);

    SDL_Texture *pTextureTxtReverse = SDL_CreateTextureFromSurface(rend, texte_reverse);
    SDL_FreeSurface(texte_reverse);

    SDL_QueryTexture(pTextureTxtScore, NULL, NULL, &txtW, &txtH);

    SDL_Rect t_score;
    t_score.x = 450;
    t_score.y = 210;
    t_score.w = txtW;
    t_score.h = txtH;

    SDL_Rect spaceRect;
    spaceRect.x = 400;
    spaceRect.y = 200;
    spaceRect.w = txtW + 100;
    spaceRect.h = txtH + 20;

    SDL_QueryTexture(pTextureTxtstart, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_start;
    t_start.x = 415;
    t_start.y = 240;
    t_start.w = txtW;
    t_start.h = txtH;

    SDL_QueryTexture(pTextureTxtsneak, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_sneak;
    t_sneak.x = 615;
    t_sneak.y = 240;
    t_sneak.w = txtW;
    t_sneak.h = txtH;

    SDL_QueryTexture(pTextureTxtReverse, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_reverse;
    t_reverse.x = 600;
    t_reverse.y = 120;
    t_reverse.w = txtW;
    t_reverse.h = txtH;

    SDL_Surface *imageSurface = IMG_Load("./picture/flecheDown.png");

    SDL_Texture *pTextureTxtFleche = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("./picture/flecheUp.png");

    SDL_Texture *pTextureTxtFlecheUp = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    SDL_Rect t_arrow;
    t_arrow.x = 630;
    t_arrow.y = 190;
    t_arrow.w = 40;
    t_arrow.h = 40;

    SDL_Rect t_arrowUp;
    t_arrowUp.x = 630;
    t_arrowUp.y = 140;
    t_arrowUp.w = 40;
    t_arrowUp.h = 40;

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawRect(rend, &spaceRect);
    SDL_RenderCopy(rend, pTextureTxtFleche, NULL, &t_arrow);

    SDL_RenderDrawRect(rend, &t_arrow);
    if (!choix)
    {
        SDL_RenderCopy(rend, pTextureTxtFlecheUp, NULL, &t_arrowUp);
        SDL_RenderDrawRect(rend, &t_arrowUp);
        SDL_RenderCopy(rend, pTextureTxtReverse, nullptr, &t_reverse);
    }

    SDL_RenderCopy(rend, pTextureTxtsneak, nullptr, &t_sneak);
    SDL_RenderCopy(rend, pTextureTxtScore, nullptr, &t_score);
    SDL_RenderCopy(rend, pTextureTxtstart, nullptr, &t_start);
}

// Show restart window when you died
void map::restartWindow(SDL_Renderer *rend, TTF_Font *dogica, SDL_Color blanc)
{
    SDL_Rect carreRestart;
    carreRestart.x = 350;
    carreRestart.y = 200;
    carreRestart.w = 300;
    carreRestart.h = 200;

    SDL_Rect boutonRestart;
    boutonRestart.x = 400;
    boutonRestart.y = 270;
    boutonRestart.w = 200;
    boutonRestart.h = 50;

    SDL_Rect boutonMenu;
    boutonMenu.x = 400;
    boutonMenu.y = 325;
    boutonMenu.w = 200;
    boutonMenu.h = 50;

    SDL_Surface *texte_gameOver = TTF_RenderText_Blended(dogica, "GAME OVER", blanc);
    SDL_Surface *texte_restart = TTF_RenderText_Blended(dogica, "RESTART", blanc);
    SDL_Surface *texte_menu = TTF_RenderText_Blended(dogica, "MENU", blanc);

    int txtW = 0;
    int txtH = 0;

    SDL_Texture *pTextureTxtGameOver = SDL_CreateTextureFromSurface(rend, texte_gameOver);
    SDL_FreeSurface(texte_gameOver);

    SDL_QueryTexture(pTextureTxtGameOver, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_gameOver;
    t_gameOver.x = 405;
    t_gameOver.y = 210;
    t_gameOver.w = txtW + 50;
    t_gameOver.h = txtH + 30;

    SDL_Texture *pTextureTxtRestart = SDL_CreateTextureFromSurface(rend, texte_restart);
    SDL_FreeSurface(texte_restart);

    SDL_QueryTexture(pTextureTxtRestart, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_restart;
    t_restart.x = 430;
    t_restart.y = 280;
    t_restart.w = txtW + 40;
    t_restart.h = txtH + 20;

    SDL_Texture *pTextureTxtMenu = SDL_CreateTextureFromSurface(rend, texte_menu);
    SDL_FreeSurface(texte_menu);

    SDL_QueryTexture(pTextureTxtMenu, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_menu;
    t_menu.x = 450;
    t_menu.y = 334;
    t_menu.w = txtW + 40;
    t_menu.h = txtH + 20;

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &carreRestart);

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &boutonRestart);
    SDL_RenderDrawRect(rend, &boutonMenu);

    SDL_RenderCopy(rend, pTextureTxtGameOver, nullptr, &t_gameOver);
    SDL_RenderCopy(rend, pTextureTxtMenu, nullptr, &t_menu);
    SDL_RenderCopy(rend, pTextureTxtRestart, nullptr, &t_restart);
}

// Update Mode Button in settings
void actuButtonMode(SDL_Renderer *rend, SDL_Texture *pTextureTxtMode, SDL_Rect t_mode, TTF_Font *dogica, SDL_Color blanc, bool &choix)
{
    if (choix)
    {
        string text = "Change Mode : Normal";
        const char *textMode = text.c_str();

        SDL_Surface *texte_mode = TTF_RenderText_Blended(dogica, textMode, blanc);

        int txtW = 0;
        int txtH = 0;

        SDL_Texture *pTextureTxtMode = SDL_CreateTextureFromSurface(rend, texte_mode);
        SDL_FreeSurface(texte_mode);
        SDL_QueryTexture(pTextureTxtMode, NULL, NULL, &txtW, &txtH);

        t_mode.x = 200;
        t_mode.y = 170;
        t_mode.w = txtW + 40;
        t_mode.h = txtH + 20;

        SDL_RenderCopy(rend, pTextureTxtMode, nullptr, &t_mode);
    }
    else
    {
        string text = "Change Mode : Reverse";
        const char *textMode = text.c_str();

        SDL_Surface *texte_mode = TTF_RenderText_Blended(dogica, textMode, blanc);

        int txtW = 0;
        int txtH = 0;

        SDL_Texture *pTextureTxtMode = SDL_CreateTextureFromSurface(rend, texte_mode);
        SDL_FreeSurface(texte_mode);
        SDL_QueryTexture(pTextureTxtMode, NULL, NULL, &txtW, &txtH);

        t_mode.x = 200;
        t_mode.y = 170;
        t_mode.w = txtW + 40;
        t_mode.h = txtH + 20;

        SDL_RenderCopy(rend, pTextureTxtMode, nullptr, &t_mode);
    }
}

// Update Music Button in settings
void actuButtonMusic(SDL_Renderer *rend, SDL_Texture *pTextureTxtMusic, SDL_Rect t_music, TTF_Font *dogica, SDL_Color blanc, bool &musique)
{
    if (musique)
    {
        string text = "Music : On";
        const char *textMusic = text.c_str();

        SDL_Surface *texte_music = TTF_RenderText_Blended(dogica, textMusic, blanc);

        int txtW = 0;
        int txtH = 0;

        pTextureTxtMusic = SDL_CreateTextureFromSurface(rend, texte_music);
        SDL_FreeSurface(texte_music);
        SDL_QueryTexture(pTextureTxtMusic, NULL, NULL, &txtW, &txtH);

        t_music.x = 200;
        t_music.y = 270;
        t_music.w = txtW + 40;
        t_music.h = txtH + 20;

        SDL_RenderCopy(rend, pTextureTxtMusic, nullptr, &t_music);
    }
    else
    {
        string text = "Music : Off";
        const char *textMusic = text.c_str();

        SDL_Surface *texte_music = TTF_RenderText_Blended(dogica, textMusic, blanc);

        int txtW = 0;
        int txtH = 0;

        pTextureTxtMusic = SDL_CreateTextureFromSurface(rend, texte_music);
        SDL_FreeSurface(texte_music);
        SDL_QueryTexture(pTextureTxtMusic, NULL, NULL, &txtW, &txtH);

        t_music.x = 200;
        t_music.y = 270;
        t_music.w = txtW + 40;
        t_music.h = txtH + 20;

        SDL_RenderCopy(rend, pTextureTxtMusic, nullptr, &t_music);
    }
}
