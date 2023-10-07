#include "dino.h"
#include "SDL2/SDL_image.h"
#include "fileCreateWrite.cpp"

// Check Collision between 2 rect
bool checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{

    if (rectA.x + rectA.w - 15 >= rectB.x &&
        rectA.x <= rectB.x + rectB.w - 15 &&
        rectA.y + rectA.h - 10 >= rectB.y &&
        rectA.y <= rectB.y + rectB.h)
    {

        return true;
    }

    return false;
}

// Set clip for animation
void dino::set_clips(SDL_Renderer *rend)
{

    SDL_Surface *imageSurface = IMG_Load("./picture/spriteDino.png");
    this->imageTexture = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("./picture/spriteDinoInverse.png");
    this->imageTextureInverse = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

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

// dino constructor
dino::dino(SDL_Renderer *rend)
{
    SDL_Rect a = {
        100,
        420,
        60, 80};

    this->hitbox = a;
    this->set_clips(rend);
}
// dino destructor
dino::~dino()
{
}

// Get functions
SDL_Rect dino::getHitbox()
{
    return this->hitbox;
}

// Set functions
void dino::setHitbox(SDL_Rect h)
{
    this->hitbox = h;
}

// Show dino
void dino::show(SDL_Renderer *rend)
{

    if (this->hitbox.y <= 460)
    {
        SDL_RenderCopy(rend, this->imageTexture, &this->currentClip, &this->hitbox);
    }
    else if (this->hitbox.y >= 500)
    {
        SDL_RenderCopy(rend, this->imageTextureInverse, &this->currentClip, &this->hitbox);
    }
}

// Dino animation
void dino::animationDino()
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

// Dino event
void dino::dinoEvent(SDL_Event &event, map &m, bool &stop)
{

    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {
        case SDL_QUIT:
            // Quit

            stop = true;

            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                if (!m.getMode())
                {
                    this->up = true;
                    this->reverse();
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

// Apply gravity on dino for jump
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

// Reverse dino position for Reverse mode
void dino::reverse()
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

// Sneak dino to pass obtacles
void dino::sneak()
{
    if (!this->jump)
    {
        if (this->hitbox.y <= 460)
        {

            if (this->down && this->goSneak)
            {
                this->animationDino();

                this->goSneak = false;
                this->hitbox.h = 40;
                this->hitbox.w = 80;
                this->hitbox.y += 40;
            }
            else if (!this->down && !this->goSneak)
            {
                this->animationDino();
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
                this->animationDino();

                this->goSneak = false;
                this->hitbox.h = 40;
            }
            else if (!this->down && !this->goSneak)
            {
                this->animationDino();
                this->goSneak = true;
                this->hitbox.h = 80;
            }
        }
    }
}

// Check collision between dino and obstacles
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
    for (int i = 0; i < m.getIndiceDoubleCactus(); i++)
    {
        if (checkCollision(this->hitbox, m.getDoubleCactus()[i].hitbox))
        {

            close = true;
        }
    }
    if (m.getSpawnMur())
    {
        if (checkCollision(this->hitbox, m.getMur()))
        {

            close = true;
        }
    }
}
