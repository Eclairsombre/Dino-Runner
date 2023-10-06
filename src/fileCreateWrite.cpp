#include <iostream>
#include <fstream>

bool verifierEtCreerFichier(const char *nomFichier)
{
    std::ifstream file(nomFichier);
    if (file.good())
    {
        // Le fichier existe déjà
        return true;
    }
    else
    {
        std::ofstream newFile(nomFichier);
        if (newFile.is_open())
        {
            // Le fichier a été créé
            newFile.close();
            return true;
        }
        else
        {
            // Erreur lors de la création du fichier
            return false;
        }
    }
}
bool ecrireDansFichier(const char *nomFichier, const char *texte)
{
    std::ofstream fichier(nomFichier, std::ios_base::app); // Mode "ajout"

    if (fichier.is_open())
    {
        fichier << texte << std::endl; // Écriture dans le fichier avec un saut de ligne
        fichier.close();
        return true; // Écriture réussie
    }
    else
    {
        return false; // Erreur lors de l'ouverture du fichier
    }
}