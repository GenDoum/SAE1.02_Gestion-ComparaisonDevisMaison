//
// Created by Mathéo Hersan on 03/01/2024.
//

#ifndef SAE1_02_AFFICHAGE_H
#define SAE1_02_AFFICHAGE_H

#include "tache.h"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define RED "\033[31m"
#define GREEN "\033[92m"
#define PURPLE "\033[35m"  // Nouvelle couleur pour le violet
#define BLUE "\033[94m"
#define MAGENTA "\033[95m"
#define CYAN "\033[96m"

/**
 * @brief Affiche les précédences entre les tâches à partir d'un fichier.
 *
 * Cette fonction lit un fichier contenant des paires de tâches et affiche leurs précédences.
 * Les paires de tâches sont lues ligne par ligne du fichier, et les précédences sont affichées
 * sur la sortie standard.
 *
 * @param nomFichier Le nom du fichier à partir duquel lire les précédences.
 */
 void afficherPrecedences(char* nomFichier);

/**
* @brief Affiche les informations de tous les devis dans une liste de devis.
*
* Cette fonction parcourt une liste de devis et affiche les informations de chaque devis.
* Les informations affichées incluent le nom de la tâche, le nom de l'entreprise, l'adresse,
* le capital, la durée et le coût du devis.
*
* @param l La liste de devis à afficher.
* @param nbDevis Le numéro de l'offre associée aux devis.
*/
void afficherListeDevis(ListeDevis l, int nbDevis);

/**
 * @brief Affiche les informations de toutes les offres.
 *
 * Cette fonction parcourt un tableau d'offres et affiche les informations de chaque offre.
 * Pour chaque offre, elle affiche le type de travaux et la liste des devis associés.
 *
 * @param tOffre Un tableau de pointeurs vers des structures Offre.
 * @param nbOffre Le nombre total d'offres dans le tableau.
 */
void afficher(Offre** tOffre, int nbOffre);

/**
 * @brief Affiche les devis correspondant à un type de travaux donné.
 *
 * Cette fonction permet à l'utilisateur de saisir un type de travaux.
 * Elle recherche ensuite dans un tableau d'offres tous les devis correspondant à ce type
 * et les affiche si trouvés.
 *
 * @param tOffre Un tableau de pointeurs vers des structures Offre.
 * @param nbOffre Le nombre total d'offres dans le tableau.
 */
void afficherDevisPourType(Offre** tOffre, int nbOffre);

/**
 * @brief Affiche les devis d'une entreprise donnée pour un type de travaux donné.
 *
 * Cette fonction permet à l'utilisateur de saisir un type de travaux et le nom d'une entreprise.
 * Elle recherche ensuite dans un tableau d'offres tous les devis de cette entreprise correspondant à ce type
 * et les affiche si trouvés.
 *
 * @param tOffre Un tableau de pointeurs vers des structures Offre.
 * @param nbOffre Le nombre total d'offres dans le tableau.
 */
void afficherDevisEntreprisePourType(Offre** tOffre, int nbOffre);

/**
 * @brief Affiche les précédences
 * 
 * Cette fonction permet à l'utilisateur d'afficher les précédences.
 * 
 * @param tPrec Un tableau de pointeurs vers des structures de précédence.
 * @param tLogique La nombre total de précédences total, sa taille logique.
*/
void affichPrecedence(Precedences **tPrec, int tLogique);


#endif //SAE1_02_AFFICHAGE_H
