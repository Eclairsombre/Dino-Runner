#include "dino.h"
#include "SDL2/SDL_image.h"

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

void dino::set_clips(SDL_Renderer *rend)
{

    SDL_Surface *imageSurface = IMG_Load("./picture/spriteDino.png");
    this->imageTexture = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("./picture/spriteDinoInverse.png");
    this->imageTextureInverse = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);
    // On coupe la feuille de sprite
    for (int i = 0; i < 5; i++)
    {
        this->clips[i].x = 88 * i;
        this->clips[i].y = 0;
        this->clips[i].w = 88;
        this->clips[i].h = 94;
    }
    for (int i = 0; i < 5; i++)
    {
        this->clipsInverse[i].x = 88 * i;
        this->clipsInverse[i].y = 40;
        this->clipsInverse[i].w = 88;
        this->clipsInverse[i].h = 94;
    }

    this->clipsInverse[5].x = 568;
    this->clipsInverse[5].y = 28;
    this->clipsInverse[5].w = 170;
    this->clipsInverse[5].h = 84;

    this->clipsInverse[6].x = 733;
    this->clipsInverse[6].y = 30;
    this->clipsInverse[6].w = 174;
    this->clipsInverse[6].h = 81;

    this->clips[5].x = 547;
    this->clips[5].y = 21;
    this->clips[5].w = 191;
    this->clips[5].h = 89;

    this->clips[6].x = 736;
    this->clips[6].y = 21;
    this->clips[6].w = 172;
    this->clips[6].h = 87;
}
dino::dino(SDL_Renderer *rend)
{
    SDL_Rect a = {
        100,
        420,
        60, 80};

    this->hitbox = a;
    this->set_clips(rend);
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
    if (this->hitbox.y <= 460)
    {
        SDL_RenderCopy(rend, this->imageTexture, &this->currentClip, &this->hitbox);
    }
    else if (this->hitbox.y >= 500)
    {
        SDL_RenderCopy(rend, this->imageTextureInverse, &this->currentClip, &this->hitbox);
    }
    // SDL_RenderFillRect(rend, &this->hitbox);}
}

void dino::chooseClip()
{

    if (this->hitbox.y <= 460)

    {
        if (this->jump)
        {

            this->currentClip = this->clips[0];
        }
        else if (this->animation == 1)
        {
            if (!this->down)
            {
                this->currentClip = this->clips[2];
            }
            else if (this->down)
            {
                this->currentClip = this->clips[5];
            }
            this->animation += 1;
        }
        else if (this->animation == 10)
        {
            if (!this->down)
            {
                this->currentClip = this->clips[3];
            }
            else if (this->down)
            {
                this->currentClip = this->clips[6];
            }
            this->animation += 1;
        }
        else if (this->animation == 20)
        {
            if (!this->down)
            {
                this->currentClip = this->clips[3];
            }
            else if (this->down)
            {
                this->currentClip = this->clips[6];
            }
            this->animation = 1;
        }
        else
        {
            this->animation++;
        }
    }
    else if (this->hitbox.y >= 500)
    {
        if (this->jump)
        {

            this->currentClip = this->clipsInverse[0];
        }
        else if (this->animation == 1)
        {
            if (!this->down)
            {
                this->currentClip = this->clipsInverse[2];
            }
            else if (this->down)
            {
                this->currentClip = this->clipsInverse[5];
            }
            this->animation += 1;
        }
        else if (this->animation == 10)
        {
            if (!this->down)
            {
                this->currentClip = this->clipsInverse[3];
            }
            else if (this->down)
            {
                this->currentClip = this->clipsInverse[6];
            }
            this->animation += 1;
        }
        else if (this->animation == 20)
        {
            if (!this->down)
            {
                this->currentClip = this->clipsInverse[3];
            }
            else if (this->down)
            {
                this->currentClip = this->clipsInverse[6];
            }
            this->animation = 1;
        }
        else
        {
            this->animation++;
        }
    }
}

void dino::moveDino(SDL_Event &event, map &m, bool &stop)
{

    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {
        case SDL_QUIT:
            // Quit
            stop = true;
            // m.setClose();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                if (!m.getMode())
                {
                    this->up = true;
                    this->changeSens();
                }
                break;
            case SDL_SCANCODE_DOWN:
                if (!this->jump)
                {
                    this->down = true;
                    this->sneak();
                }

                break;
            case SDL_SCANCODE_SPACE:
                if (!this->down)
                {
                    this->jump = true;
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
                if (!m.getMode())
                {
                    this->up = false;
                }

                break;
            case SDL_SCANCODE_DOWN:
                if (!this->jump)
                {
                    this->down = false;
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
    else if (this->hitbox.y >= 550)
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

        if (this->hitbox.y + vy < 550)
        {
            this->hitbox.y = 550;
            vy = 0;
            jump = false;
            goUp = true;
        }

        this->hitbox.y += this->vy;
    }
}

void dino::changeSens()
{
    if (!this->down)
    {
        if (!this->jump)
        {
            if (this->hitbox.y == 420)
            {

                this->hitbox.y = 550;
            }
            else if (this->hitbox.y == 550)
            {

                this->hitbox.y = 420;
            }
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
                this->chooseClip();

                this->goSneak = false;
                this->hitbox.h = 40;
                this->hitbox.w = 80;
                this->hitbox.y += 40;
            }
            else if (!this->down && !this->goSneak)
            {
                this->chooseClip();
                this->goSneak = true;
                this->hitbox.h = 80;
                this->hitbox.w = 60;
                this->hitbox.y -= 40;
            }
        }
        else if (this->hitbox.y >= 500)
        {

            if (this->down && this->goSneak)
            {
                this->chooseClip();

                this->goSneak = false;
                this->hitbox.h = 40;
            }
            else if (!this->down && !this->goSneak)
            {
                this->chooseClip();
                this->goSneak = true;
                this->hitbox.h = 80;
                        }
        }
    }
}

void dino::collision(map &m, bool &close)
{
    for (int i = 0; i < m.getIndiceCactus(); i++)
    {
        if (checkCollision(this->hitbox, m.getCactus()[i].hitbox))
        {

            close = true;
        }
    }
    for (int i = 0; i < m.getIndiceOiseau(); i++)
    {
        if (checkCollision(this->hitbox, m.getOiseau()[i].hitbox))
        {

            close = true;
        }
    }
}
