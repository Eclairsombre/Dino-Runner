
#ifndef MAP
#define MAP

#include <SDL2/SDL.h>

class map
{
private:
    SDL_Rect elt[100];
    SDL_Rect obstacles[100];
    int indice;

    bool spawn, close;

public:
    map(/* args */);
    ~map();
    bool getClose();
    void setClose();
};

#endif