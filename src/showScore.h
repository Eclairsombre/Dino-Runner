#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int findMaxNumber(const char *nomFichier);
vector<string> CatchLastLignes(const char *nomFichier, int nombreLignes);
void showScore(SDL_Renderer *rend, vector<string> lignes, TTF_Font *dogica, SDL_Color blanc);