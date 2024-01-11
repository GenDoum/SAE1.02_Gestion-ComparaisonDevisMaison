//
// Created by Mathéo Hersan on 05/01/2024.
//

#ifndef SAE1_02_UTILS_H
#define SAE1_02_UTILS_H
#include "tache.h"
#include "../struct.h"

/**
 * @brief Crée une liste de devis vide.
 *
 * Cette fonction crée et retourne une liste de devis vide.
 *
 * @return Une liste de devis vide.
 */
ListeDevis listeVide(void);

/**
 * @brief Insère un nouveau maillon au début d'une liste de devis.
 *
 * Cette fonction crée un nouveau maillon de devis avec les informations fournies
 * et l'insère au début de la liste de devis spécifiée.
 *
 * @param l La liste de devis où insérer le nouveau maillon.
 * @param nomTache Le nom de la tâche pour le nouveau maillon.
 * @param entreprise Le nom de l'entreprise pour le nouveau maillon.
 * @param adresse Les détails de l'adresse pour le nouveau maillon.
 * @param capital Le capital de l'entreprise pour le nouveau maillon.
 * @param duree La durée de la tâche pour le nouveau maillon.
 * @param cout Le coût de la tâche pour le nouveau maillon.
 * @return La liste de devis mise à jour avec le nouveau maillon en tête.
 */
ListeDevis insererEnTete(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout);

/**
 * @brief Insère un nouveau maillon de devis dans une liste de manière croissante selon le nom de la tâche.
 *
 * Cette fonction insère un nouveau maillon de devis dans une liste de devis de manière à maintenir
 * l'ordre croissant des noms de tâches. Si le nom de tâche est identique à un maillon existant, le nouveau
 * maillon sera inséré après tous les maillons avec le même nom de tâche.
 *
 * @param l La liste de devis où insérer le nouveau maillon.
 * @param nomTache Le nom de la tâche pour le nouveau maillon.
 * @param entreprise Le nom de l'entreprise pour le nouveau maillon.
 * @param adresse Les détails de l'adresse pour le nouveau maillon.
 * @param capital Le capital de l'entreprise pour le nouveau maillon.
 * @param duree La durée de la tâche pour le nouveau maillon.
 * @param cout Le coût de la tâche pour le nouveau maillon.
 * @return La liste de devis mise à jour avec le nouveau maillon inséré de manière croissante.
 */
ListeDevis insertionCroissante(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout);

/**
 * @brief Vérifie si un nom de tâche appartient à une liste de devis.
 *
 * Cette fonction parcourt la liste de devis et vérifie si le nom de tâche spécifié
 * est présent dans la liste.
 *
 * @param l La liste de devis à parcourir.
 * @param nomTache Le nom de la tâche à rechercher.
 * @return 1 si le nom de tâche est trouvé dans la liste, 0 sinon.
 */
int appartient(ListeDevis l, char* nomTache);

/**
 * @brief Trie un tableau d'offres selon le nom des travaux en utilisant l'algorithme QuickSort.
 *
 * Cette fonction trie le tableau d'offres selon le nom des travaux en utilisant l'algorithme QuickSort.
 *
 * @param tOffre Le tableau d'offres à trier.
 * @param tLogique Le nombre d'éléments logiques dans le tableau.
 */
void quickSort(Offre** tOffre, int tLogique);

/**
 * @brief Recherche une tâche spécifique dans un tableau d'offres à l'aide de la recherche dichotomique.
 *
 * Cette fonction recherche une tâche spécifique dans un tableau d'offres en utilisant l'algorithme de recherche dichotomique.
 * Elle renvoie la position de la tâche si elle est trouvée, sinon elle indique la position où la tâche devrait être insérée.
 *
 * @param tOffre Le tableau d'offres où effectuer la recherche.
 * @param tLogique Le nombre d'éléments logiques dans le tableau.
 * @param nomTache Le nom de la tâche à rechercher.
 * @param trouve Un pointeur vers un entier qui sera mis à 1 si la tâche est trouvée, 0 sinon.
 * @return La position de la tâche si elle est trouvée, sinon la position d'insertion.
 */
int rechercheDichotomique(Offre** tOffre, int tLogique, char* nomTache, int* trouve);

/**
 * @brief Ajoute un nouveau devis à un tableau d'offres et trie la liste de devis associée.
 *
 * Cette fonction ajoute un nouveau devis à un tableau d'offres. Elle recherche d'abord la position
 * où insérer le nouveau devis en utilisant la recherche dichotomique, puis insère le devis de manière
 * croissante dans la liste de devis correspondante.
 *
 * @param tOffre Le tableau d'offres où ajouter le nouveau devis.
 * @param nbDevis Le nombre actuel de devis dans le tableau.
 * @param nomTache Le nom de la tâche pour le nouveau devis.
 * @param entreprise Le nom de l'entreprise pour le nouveau devis.
 * @param adresse Les détails de l'adresse pour le nouveau devis.
 * @param capital Le capital de l'entreprise pour le nouveau devis.
 * @param duree La durée de la tâche pour le nouveau devis.
 * @param cout Le coût de la tâche pour le nouveau devis.
 */
void nouveauDevis(Offre** tOffre, int nbDevis, char* nomTache, char* entreprise, Adresse adresse, int capital, int duree, int cout);

/**
 * @brief Vérifie si une liste de devis est vide.
 *
 * Cette fonction vérifie si une liste de devis est vide.
 *
 * @param l La liste de devis à vérifier.
 * @return true si la liste est vide, false sinon.
 */
bool vide(ListeDevis l);

/**
 * @brief Calcule la longueur d'une liste de devis.
 *
 * Cette fonction calcule la longueur (le nombre de maillons) d'une liste de devis.
 *
 * @param l La liste de devis dont calculer la longueur.
 * @return Le nombre de maillons dans la liste.
 */
int len(ListeDevis l);

/**
 * @brief Supprime un maillon contenant un devis spécifique d'une liste de devis.
 *
 * Cette fonction supprime un maillon contenant un devis spécifique de la liste de devis donnée.
 * Si le maillon à supprimer est en tête de liste, elle utilise la fonction supprimerEnTete.
 * Elle parcourt récursivement la liste jusqu'à trouver le maillon à supprimer.
 *
 * @param l La liste de devis où supprimer le maillon.
 * @param nomTache Le nom de la tâche du devis à supprimer.
 * @return La liste mise à jour après suppression.
 */
//ListeDevis supprimer(ListeDevis l, char* nomTache);

/**
 * @brief Supprime le maillon en tête d'une liste de devis.
 *
 * Cette fonction supprime le maillon en tête de la liste de devis donnée et libère la mémoire associée.
 *
 * @param l La liste de devis où supprimer le maillon en tête.
 * @return La liste mise à jour après suppression.
 */
ListeDevis supprimerEnTete(ListeDevis l);

/**
 * @brief Supprime un devis spécifique de toutes les offres dans un tableau d'offres.
 *
 * Cette fonction demande à l'utilisateur le nom de la tâche à supprimer, puis parcourt
 * toutes les offres dans le tableau d'offres pour supprimer le devis correspondant de la liste de devis.
 *
 * @param tOffre Le tableau d'offres où supprimer le devis.
 * @param nb Le nombre d'offres dans le tableau d'offres.
 */
void supprimerDevis(Offre** tOffre, int nb);
void supprimerMauvaisDevis(Offre** tOffre, int i, MaillonDevis* meilleurDevis);

#endif //SAE1_02_UTILS_H
