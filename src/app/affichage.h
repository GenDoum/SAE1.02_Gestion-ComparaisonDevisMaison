//
// Created by Mathéo Hersan on 03/01/2024.
//

#ifndef SAE1_02_AFFICHAGE_H
#define SAE1_02_AFFICHAGE_H

#include "tache.h"

/**
 * @brief Affiche les precedences
 *
 * @param nomFichier le nom du fichier
 * @return void
 */
void afficherPrecedences(char* nomFichier);

/**
 * @brief Affiche les Offres
 *
 * @param tOffre le tableau d'offres
 * @param nbOffres la taille logique du tableau d'offres
 * @return void
 */
//void afficherOffres(Offre** tOffre, int nbOffres);

/**
 * @brief Affiche les devis par type de travaux
 *
 * @param tOffre le tableau d'offres
 * @param nbDevis la taille logique du tableau d'offres
 */
//void afficherDevisParTypeTravaux(Offre** tOffre, int nbDevis);

/**
 * @brief Affiche les devis par entreprise
 *
 * @param tOffre le tableau d'offres
 * @param nbDevis la taille logique du tableau d'offres
 */
//void afficherUnTravaux(Offre* offre);

/**
 * @brief Affiche les devis par entreprise et par type de travaux
 *
 * @param tOffre le tableau d'offres
 * @param nbDevis la taille logique du tableau d'offres
 */
//void afficherDevisEntrepriseType(Offre** tOffre, int nbDevis);


void afficherListeDevis(ListeDevis l, int nbDevis);


void afficher(Offre** tOffre, int nbOffre);
void afficherDevisPourType(Offre** tOffre, int nbOffre);
void afficherDevisEntreprisePourType(Offre** tOffre, int nbOffre);

#endif //SAE1_02_AFFICHAGE_H
