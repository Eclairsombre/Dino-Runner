#include "dino.h"

dino::dino()
{
    SDL_Rect a;
    a.h = 80;
    a.w = 60;
    a.x = 100;
    a.y = 440;

    this->hitbox = a;
    this->sens = "haut";
}

dino::~dino()
{
}

SDL_Rect dino::getHitbox()
{
    return this->hitbox;
}

string dino::getSens()
{
    return this->sens;
}

void dino::show(SDL_Renderer *rend)
{

    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderFillRect(rend, &this->hitbox);
}

void dino::moveDino(SDL_Event &event, map &m)
{

    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {
        case SDL_QUIT:
            // Quit
            m.setClose();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                up = true;
                break;
            case SDL_SCANCODE_DOWN:
                down = true;
                break;
            case SDL_SCANCODE_SPACE:

                break;

            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                up = false;
                break;
            case SDL_SCANCODE_DOWN:
                down = false;
                /*d.hitbox.h = 60;
                if (d.sens.compare("haut") == 0)
                {
                    d.hitbox.y -= 30;
                    temp = false;
                }*/
                break;

            default:
                break;
            }
            break;
        }
    }
}
void dino::Gravity()
{
}
