#include <SDL2/SDL.h>
class map
{
private:
    /* data */
public:
    SDL_Rect elt[100];
    SDL_Rect obstacles[100];
    int indice;

    bool spawn;
};
