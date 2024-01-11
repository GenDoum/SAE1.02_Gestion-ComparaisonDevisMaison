#ifndef SAE1_02_CHARGEMENT_H
#define SAE1_02_CHARGEMENT_H

#include "../struct.h"
#include "utils.h"
#include "affichage.h"
#define MAX_TACHES 100


/**
 * @brief Charge les données des offres à partir d'un fichier.
 *
 * Cette fonction lit un fichier contenant des informations sur des offres et les charge dans un tableau dynamique.
 * Elle utilise une approche de recherche dichotomique pour insérer les nouvelles offres dans le tableau.
 *
 * @param nomFichier Le nom du fichier à partir duquel lire les données.
 * @param nbOffre Un pointeur vers le nombre total d'offres.
 * @param max Un pointeur vers la capacité maximale du tableau.
 * @return Un tableau de pointeurs vers des structures Offre contenant les données chargées.
 */
Offre** chargement(char* nomFichier, int* nbOffre, int* max);

int chargerTache(Offre** tOffre, Tache** tTache, ListeFile * fileAttente, int nbrTache, char* nomFichier);

#endif //SAE1_02_CHARGEMENT_H
