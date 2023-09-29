
#ifndef MAP
#define MAP

#include <SDL2/SDL.h>
#include <vector>

class map
{
private:
    SDL_Rect sol, oiseau, cactus;
    vector<SDL_Rect> obstacles;
    int vx, spawnRate;
    long timer;
    bool spawn = true, close;

public:
    map(/* args */);
    ~map();
    bool getClose();
    void setClose();
    void show(SDL_Renderer *rend);
    void addObstacle();
    void moveObstacle();
    vector<SDL_Rect> getObstacles();
};

#endif