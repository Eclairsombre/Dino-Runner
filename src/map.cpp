#include "map.h"
#include <iostream>

#include "SDL2/SDL_image.h"
using namespace std;

void sup_case(int i, int &indice, cactus tab_block[500], oiseau oi[500])
{
    // Supprime une case d'un tab
    if (tab_block != NULL)
    {
        for (int y = i; y <= indice; y++)
        {
            tab_block[y] = tab_block[y + 1];
        }
    }
    if (oi != NULL)
    {
        for (int y = i; y <= indice; y++)
        {
            oi[y] = oi[y + 1];
        }
    }
}

void oiseau::set_clips()
{

    this->clip1.x = 87;
    this->clip1.y = 5;
    this->clip1.w = 94;
    this->clip1.h = 77;

    this->clip2.x = 180;
    this->clip2.y = 0;
    this->clip2.w = 95;
    this->clip2.h = 64;

    this->hitbox.h = 60;
    this->hitbox.w = 60;
    this->hitbox.x = 1020;
    this->hitbox.y = 380;

    this->clipActuel = this->clip1;
}

void cactus::set_clipsCactus()
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

    this->spawnRate = 4;
    this->sol = s;

    this->close = false;
    this->vx = 4;

    SDL_Surface *imageSurface = IMG_Load("./picture/sprite.png");

    this->imageOiseau = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);
}

void map::chooseClip()
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
map::~map()
{
}

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
int map::getIndiceOiseau()
{
    return this->indiceOiseau;
}

cactus *map::getCactus()
{
    return this->cac;
}

void map::setMode(bool choix)
{

    this->mode1 = choix;
}
void map::setClose()
{
    this->close = true;
}

void map::addObstacle(SDL_Renderer *rend)
{
    this->timer = SDL_GetTicks();

    if (this->timer / 1000 % this->spawnRate == 0 && this->spawn)
    {
        this->spawn = false;
        int nb = rand() % 2;
        oiseau o;
        o.set_clips();
        cactus c;
        c.set_clipsCactus();

        switch (nb)
        {
        case 0:
            cout << o.hitbox.x << endl;
            this->oi[this->indiceOiseau] = o;
            this->indiceOiseau += 1;

            break;

        case 1:
            cout << c.hitbox.x << endl;
            this->cac[this->indiceCactus] = c;
            this->indiceCactus += 1;
            break;

        default:
            break;
        }
    }
    if (this->timer / 1000 % this->spawnRate != 0 && this->spawn == false)
    {
        this->spawn = true;
    }
}

void map::moveObstacle()
{

    for (int i = 0; i < this->indiceCactus; i++)
    {

        this->cac[i].hitbox.x -= this->vx;

        if (this->cac[i].hitbox.x < -50)
        {
            sup_case(i, this->indiceCactus, this->cac, NULL);
            indiceCactus -= 1;
        }
    }

    for (int i = 0; i < this->indiceOiseau; i++)
    {

        this->oi[i].hitbox.x -= this->vx;

        if (this->oi[i].hitbox.x < -50)
        {
            sup_case(i, this->indiceOiseau, NULL, this->oi);
            indiceOiseau -= 1;
        }
    }
}

void map::show(SDL_Renderer *rend)
{

    for (int i = 0; i < this->indiceCactus; i++)
    {
        // SDL_RenderFillRect(rend, &this->cac[i].hitbox);

        SDL_RenderCopy(rend, this->imageOiseau, &this->cac[i].clipActuel, &this->cac[i].hitbox);
    }
    for (int i = 0; i < this->indiceOiseau; i++)
    {

        SDL_RenderCopy(rend, this->imageOiseau, &this->oi[i].clipActuel, &this->oi[i].hitbox);
    }
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &this->sol);
}
