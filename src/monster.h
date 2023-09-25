#include <SDL2/SDL.h>

class monster
{

public:
    SDL_Rect MonsterRect;
    int x_base, y_base;
    string direction;

    void InitMonster(monster &m);
    void MonsterWalk(monster &m);
};
