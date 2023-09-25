#include "map.h"

void initialiseMap(map &m)
{
    SDL_Rect sol;
    sol.h = 100;
    sol.w = 2000;
    sol.x = -20;
    sol.y = 500;

    m.elt[0] = sol;
    m.indice = 0;
}

void afficherMap(map &m, SDL_Renderer *rend)
{
    for (int i = 0; i <= m.indice; i++)
    {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderFillRect(rend, &m.elt[i]);
    }
}