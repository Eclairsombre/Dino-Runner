#ifndef DINO
#define DINO

#include <SDL2/SDL.h>
#include "map.cpp"

class dino
{
private:
    SDL_Rect hitbox;
    string sens;
    bool up = false, down = false, right = false, left = false;
    /* data */
public:
    dino();
    ~dino();
    SDL_Rect getHitbox();
    string getSens();
    void show(SDL_Renderer *rend);
    void Gravity();
    void moveDino(SDL_Event &event, map &m);
};

#endif