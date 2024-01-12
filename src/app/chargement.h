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

/**
 * @brief Charge les informations des tâches à partir d'un fichier et initialise les structures associées.
 *
 * Cette fonction lit un fichier spécifié, extrait les informations sur les précédences entre les tâches,
 * et initialise les structures nécessaires pour représenter les tâches et leurs relations.
 *
 * @param tOffre Le tableau des offres de travaux.
 * @param tTache Le tableau des tâches à initialiser.
 * @param file La file d'attente pour le traitement des tâches.
 * @param tLogique Le nombre total d'éléments dans les tableaux.
 * @param nomFichier Le nom du fichier contenant les informations sur les précédences.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int chargerTache(Offre** tOffre, Tache** tTache, ListeFile * file, int nbrTache, char* nomFichier);

#endif //SAE1_02_CHARGEMENT_H
