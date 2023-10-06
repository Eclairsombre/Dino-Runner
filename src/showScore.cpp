#include <fstream>
#include <iostream>
using namespace std;
#include <string.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <vector>
int trouverPlusGrandNombre(const char *nomFichier)
{
    std::ifstream fichier("../file/score.txt");
    int plusGrandNombre = 0;

    if (fichier.is_open())
    {
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            try
            {
                int nombre = std::stoi(ligne);
                if (nombre > plusGrandNombre)
                {
                    plusGrandNombre = nombre;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Erreur de conversion : " << e.what() << std::endl;
            }
        }
        fichier.close();
    }
    else
    {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }

    return plusGrandNombre;
}

std::vector<std::string> obtenirDernieresLignes(const char *nomFichier, int nombreLignes)
{
    std::ifstream fichier(nomFichier);
    std::vector<std::string> lignes;
    std::string ligne;

    if (fichier.is_open())
    {
        while (std::getline(fichier, ligne))
        {
            lignes.push_back(ligne);
            if (lignes.size() > nombreLignes)
            {
                lignes.erase(lignes.begin());
            }
        }
        fichier.close();
    }
    else
    {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }

    return lignes;
}
void showScore(SDL_Renderer *rend, vector<string> lignes, TTF_Font *dogica, SDL_Color blanc)
{

    int highscore = trouverPlusGrandNombre("../file/score.txt");
    int txtW = 0;
    int txtH = 0;
    const char *score = to_string(highscore).c_str();
    SDL_Surface *texte_highscore = TTF_RenderText_Blended(dogica, score, blanc);

    SDL_Texture *pTextureTxtHighScore = SDL_CreateTextureFromSurface(rend, texte_highscore);
    SDL_FreeSurface(texte_highscore);

    SDL_QueryTexture(pTextureTxtHighScore, NULL, NULL, &txtW, &txtH);
    SDL_Rect t_highscore;
    t_highscore.x = 100;
    t_highscore.y = 200;
    t_highscore.w = txtW;
    t_highscore.h = txtH;

    SDL_Surface *texte_score;
    SDL_Texture *pTextureTxtScore;
    SDL_Rect t_score;

    SDL_RenderCopy(rend, pTextureTxtHighScore, nullptr, &t_highscore);
    const char *s;
    for (int i = 0; i < lignes.size(); i++)
    {

        s = (lignes[i]).c_str();
        texte_score = TTF_RenderText_Blended(dogica, s, blanc);

        pTextureTxtScore = SDL_CreateTextureFromSurface(rend, texte_score);
        SDL_FreeSurface(texte_score);

        SDL_QueryTexture(pTextureTxtScore, NULL, NULL, &txtW, &txtH);

        t_score.x = 350;
        t_score.y = 200 + 30 * i;
        t_score.w = txtW;
        t_score.h = txtH;

        SDL_RenderCopy(rend, pTextureTxtScore, nullptr, &t_score);
    }
}