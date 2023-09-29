#include "map.h"
#include <iostream>
using namespace std;

map::map(/* args */)
{
    SDL_Rect s;
    s.h = 60;
    s.w = 1000;
    s.x = 0;
    s.y = 500;

    SDL_Rect o;
    o.h = 30;
    o.w = 40;
    o.x = 1020;
    o.y = 400;

    SDL_Rect c;
    c.h = 40;
    c.w = 20;
    c.x = 1020;
    c.y = 460;

    this->spawnRate = 4;
    this->sol = s;
    this->oiseau = o;
    this->cactus = c;
    this->close = false;
    this->vx = 4;
}

map::~map()
{
}

bool map::getClose()
{
    return this->close;
}

vector<SDL_Rect> map::getObstacles()
{
    return this->obstacles;
}
void map::setClose()
{
    this->close = true;
}

void map::addObstacle()
{
    this->timer = SDL_GetTicks();
    if (this->timer / 1000 % this->spawnRate == 0 && this->spawn)
    {
        this->spawn = false;
        int nb = rand() % 2;

        switch (nb)
        {
        case 0:
            this->obstacles.push_back(oiseau);
            break;

        case 1:
            this->obstacles.push_back(cactus);
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
    for (int i = 0; i < this->obstacles.size(); i++)
    {

        this->obstacles[i].x -= this->vx;

        if (this->obstacles[i].x < -50)
        {
            this->obstacles.erase(this->obstacles.begin() + i - 1);
        }
    }
}

void map::show(SDL_Renderer *rend)
{

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &this->sol);
    for (int i = 0; i < this->obstacles.size(); i++)
    {
        SDL_RenderFillRect(rend, &this->obstacles[i]);
    }
}

void sup_case(int i, int &indice, SDL_Rect elt[100])
{
    // Supprime une case d'un tab de block
    for (int y = i; y <= indice; y++)
    {
        elt[y] = elt[y + 1];
    }
}
