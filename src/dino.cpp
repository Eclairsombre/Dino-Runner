#include "dino.h"

bool checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    // Vérifie si les rectangles se chevauchent en utilisant les coordonnées de leurs coins.
    if (rectA.x + rectA.w >= rectB.x && // Coin droit de A est à droite de B
        rectA.x <= rectB.x + rectB.w && // Coin gauche de A est à gauche de B
        rectA.y + rectA.h >= rectB.y && // Coin bas de A est en dessous de B
        rectA.y <= rectB.y + rectB.h)   // Coin haut de A est au-dessus de B
    {
        // Les rectangles se chevauchent
        return true;
    }
    // Aucune collision
    return false;
}
dino::dino()
{
    SDL_Rect a;
    a.h = 80;
    a.w = 60;
    a.x = 100;
    a.y = 420;

    this->hitbox = a;
}

dino::~dino()
{
}

SDL_Rect dino::getHitbox()
{
    return this->hitbox;
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
                if (!this->jump)
                {
                    down = true;
                    this->sneak();
                }

                break;
            case SDL_SCANCODE_SPACE:
                if (!this->down)
                {
                    jump = true;
                }
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
                if (!this->jump)
                {
                    down = false;
                    this->sneak();
                }
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

    if (this->hitbox.y <= 420)
    {
        if (jump)
        {
            if (this->hitbox.y > 300 && goUp)
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
    else if (this->hitbox.y >= 560)
    {
        if (jump)
        {
            if (this->hitbox.y < 680 && goUp)
            {

                vy += g;
            }
            else if (this->hitbox.y > 680)
            {
                goUp = false;
                vy -= g;
            }
        }

        if (this->hitbox.y + vy < 560)
        {
            this->hitbox.y = 560;
            vy = 0;
            jump = false;
            goUp = true;
        }

        this->hitbox.y += this->vy;
    }
}

void dino::changeSens()
{
    if (!this->jump)
    {
        if (this->hitbox.y == 420)
        {

            this->hitbox.y = 560;
        }
        else if (this->hitbox.y == 560)
        {

            this->hitbox.y = 420;
        }
    }
}

void dino::sneak()
{
    if (!this->jump)
    {
        if (this->hitbox.y <= 460)
        {

            if (this->down && this->goSneak)
            {

                this->goSneak = false;
                this->hitbox.h = 40;
                this->hitbox.y += 40;
            }
            else if (!this->down && !this->goSneak)
            {
                this->goSneak = true;
                this->hitbox.h = 80;
                this->hitbox.y -= 40;
            }
        }
        else if (this->hitbox.y >= 500)
        {

            if (this->down && this->goSneak)
            {

                this->goSneak = false;
                this->hitbox.h = 40;
            }
            else if (!this->down && !this->goSneak)
            {
                this->goSneak = true;
                this->hitbox.h = 80;
            }
        }
    }
}

void dino::collision(map &m)
{
    for (int i = 0; i < m.getObstacles().size(); i++)
    {
        if (checkCollision(this->hitbox, m.getObstacles()[i]))
        {
            m.setClose();
        }
    }
}