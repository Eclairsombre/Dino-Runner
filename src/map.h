
#ifndef MAP
#define MAP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "SDL2/SDL_image.h"
#include <string>

// Class for obstacles
class oiseau
{
public:
    SDL_Rect clip1, clip2, hitbox, clipActuel;
    int animation = 1;
    bool inverse = false;
    void set_clips();
};

class nuage
{
public:
    SDL_Rect hitbox, clipActuel;
    bool inverse = false;

    void set_clips();
};

class cactus
{
public:
    SDL_Rect hitbox, clipActuel, chooseClip[10];
    int animation = 1;
    bool inverse = false;
    void set_clipsCactus();
};

class doubleCactus
{
public:
    SDL_Rect hitbox, clipActuel, chooseClip[10];
    int animation = 1;
    bool inverse = false;
    void set_clipsDoubleCactus();
};

// Main class
class map
{
private:
    SDL_Rect sol, clips[10], murUp, murDown, mur;
    cactus cac[500];
    doubleCactus douCac[500];
    oiseau oi[500];
    nuage nu[500];
    SDL_Texture *imageOiseau, *imageOiseauInverse;
    int vx, spawnRate, indiceCactusDouble = 0, indiceNuage = 0, indiceCactus = 0, indiceOiseau = 0, score = 0;
    long timer;
    bool spawn = true, close;
    bool mode1 = true, increaseSpeed = true;
    bool mUp = false, mDown = false, spawnMur = false;

public:
    map(SDL_Renderer *rend, bool choix);
    ~map();
    bool getClose();
    void setClose();
    void show(SDL_Renderer *rend);
    void addObstacle(SDL_Renderer *rend, int time);
    void UpdateObstacle();
    bool getSpawnMur();
    SDL_Rect getMur();
    void OiseauAnimation();
    int getIndiceOiseau();
    int getIndiceCactus();
    int getIndiceDoubleCactus();
    doubleCactus *getDoubleCactus();
    cactus *getCactus();
    oiseau *getOiseau();
    bool getMode();
    void setMode(bool choix);
    void ActuVitesse(int time);
    void actuScore(SDL_Renderer *rend, int time, std::string text, SDL_Texture *pTextureTxtScore, SDL_Rect t_score, TTF_Font *dogica, SDL_Color blanc);
    int getScore();
    void showKey(SDL_Renderer *rend, TTF_Font *dogica, SDL_Color noir, bool &choix);
    void restartWindow(SDL_Renderer *rend, TTF_Font *dogica, SDL_Color blanc);
};

// Update Mode Button in settings
void actuButtonMode(SDL_Renderer *rend, SDL_Texture *pTextureTxtMode, SDL_Rect t_mode, TTF_Font *dogica, SDL_Color blanc, bool &choix);

// Update Music Button in settings
void actuButtonMusic(SDL_Renderer *rend, SDL_Texture *pTextureTxtMusic, SDL_Rect t_music, TTF_Font *dogica, SDL_Color blanc, bool &musique);


#endif