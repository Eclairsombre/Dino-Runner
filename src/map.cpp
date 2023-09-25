#include "map.h"
#include <iostream>
using namespace std;

void InitMap(map &m)
{
    for (int i = 0; i <= 20; i++)
    {
        for (int y = 0; y <= 16; y++)
        {
            m.tab[i][y] = 1;
        }
    }
}
void DrawMap(map &m, SDL_Renderer *rend)
{
    SDL_Surface *image = IMG_Load("./picture/grass.png");

    SDL_Texture *grass = SDL_CreateTextureFromSurface(rend, image); // La texture monImage contient maintenant l'image importée
    SDL_FreeSurface(image);
    SDL_Rect img;
    img.h = 100;
    img.w = 100;
    img.x = 0;
    img.y = 0;

    for (int i = 0; i <= 20; i++)
    {
        for (int y = 0; y <= 16; y++)
        {
            if (m.tab[i][y] == 1)
            {
                img.y = 100 * i;
                img.x = 100 * y;
                SDL_RenderCopy(rend, grass, nullptr, &img);
            }
        }
    }
}