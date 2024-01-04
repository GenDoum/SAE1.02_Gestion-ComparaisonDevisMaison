#ifndef SAE1_02_CHARGEMENT_H
#define SAE1_02_CHARGEMENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tache.h"

/**
 * @brief Charge les devis
 *
 * @param nomFichier le nom du fichier
 * @param tOffre le tableau d'offres
 * @return int la taille logique du tableau d'offres
 */
int chargerDevis(char* nomFichier, Offre** tOffre);

/**
 * @brief Charge les precedences
 *
 * @param nomFichier le nom du fichier
 * @return void
 */
void chargerPrecedences(char* nomFichier);

#endif //SAE1_02_CHARGEMENT_H
