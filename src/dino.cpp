#include "dino.h"

dino::dino()
{
    SDL_Rect a;
    a.h = 80;
    a.w = 60;
    a.x = 100;
    a.y = 420;

    this->hitbox = a;
    this->sens = new string("up");
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
    return *this->sens;
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
                this->changeSens();
                break;
            case SDL_SCANCODE_DOWN:
                down = true;
                break;
            case SDL_SCANCODE_SPACE:
                jump = true;
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
    string temp = this->getSens();
    if (temp == "up")
    {
        if (jump == true)
        {
            if (this->hitbox.y > 300 && goUp == true)
            {

                vy -= g;
            }
            else if (this->hitbox.y < 300)
            {
                goUp = false;
                vy += g;
            }
        }

        if (this->hitbox.y + vy > 420)
        {
            this->hitbox.y = 420;
            vy = 0;
            jump = false;
            goUp = true;
        }

        this->hitbox.y += this->vy;
    }
    else if (temp == "down")
    {
        if (jump == true)
        {
            if (this->hitbox.y > 600 && goUp == true)
            {

                vy += g;
            }
            else if (this->hitbox.y < 600)
            {
                goUp = false;
                vy -= g;
            }
        }

        if (this->hitbox.y + vy < 500)
        {
            this->hitbox.y = 500;
            vy = 0;
            jump = false;
            goUp = true;
        }

        this->hitbox.y += this->vy;
    }
}

void dino::changeSens()
{

    if (this->getSens() == "up")
    {
        delete sens;
        this->hitbox.y = 560;

        this->sens = new string("down");
    }
    else if (this->getSens() == "down")
    {
        delete sens;

        this->hitbox.y = 420;

        this->sens = new string("up");
    }
}