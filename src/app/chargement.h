#ifndef SAE1_02_CHARGEMENT_H
#define SAE1_02_CHARGEMENT_H

#include "tache.h"
#include "utils.h"

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

void chargerPrecedences(char* nomFichier);
Tache** chargerTaches(char* nomFichier);

#endif //SAE1_02_CHARGEMENT_H
