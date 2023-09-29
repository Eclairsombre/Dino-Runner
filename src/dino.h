#ifndef DINO
#define DINO

#include <SDL2/SDL.h>
#include "map.cpp"

class dino
{
private:
    SDL_Rect hitbox;

    bool up = false, down = false, jump = false, goUp = true, goSneak = true, stopSneak = false;
    int vy = 0, g = 2;

public:
    dino();
    ~dino();
    SDL_Rect getHitbox();

    string getSens();
    void show(SDL_Renderer *rend);
    void Gravity();
    void moveDino(SDL_Event &event, map &m);
    void changeSens();
    void sneak();
    void collision(map &m);
};

#endif