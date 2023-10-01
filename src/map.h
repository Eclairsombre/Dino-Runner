
#ifndef MAP
#define MAP

#include <SDL2/SDL.h>
#include <vector>
class oiseau
{
public:
    SDL_Rect clip1, clip2, hitbox, clipActuel;
    int animation = 1;
    void set_clips();
};

class cactus
{
public:
    SDL_Rect hitbox, clipActuel, chooseClip[10];
    int animation = 1;
    void set_clipsCactus();
};

class map
{
private:
    SDL_Rect sol, clips[10];
    cactus cac[500];
    oiseau oi[500];

    SDL_Texture *imageOiseau;
    int vx, spawnRate, indiceCactus = 0, indiceOiseau = 0;
    long timer;
    bool spawn = true, close;

public:
    map(SDL_Renderer *rend);
    ~map();
    bool getClose();
    void setClose();
    void show(SDL_Renderer *rend);
    void addObstacle(SDL_Renderer *rend);
    void moveObstacle();

    void chooseClip();
    int getIndice();
    cactus *getCactus();
};

#endif