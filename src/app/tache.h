#ifndef TACHE_H
#define TACHE_H
#include "affichage.h"
#include "../struct.h"

/**
 * @brief Crée une nouvelle précédence entre deux tâches et l'ajoute à un fichier.
 *
 * Cette fonction permet à l'utilisateur de créer une nouvelle précédence entre deux tâches
 * et de l'ajouter à un fichier spécifié.
 *
 * @param nomFichier Le chemin du fichier où ajouter la précédence.
 */
void creerPrecedences(char* nomFichier);

/**
 * @brief Sélectionne les meilleures entreprises pour chaque type de travaux.
 *
 * Cette fonction parcourt toutes les offres de travaux et sélectionne la meilleure entreprise pour chaque type de travaux.
 * La meilleure entreprise est déterminée en comparant le coût et le capital des entreprises associées à une tâche.
 * Les entreprises moins avantageuses sont ajoutées à une liste à supprimer.
 * Après la sélection, les mauvais devis sont supprimés des offres.
 *
 * @param tOffre Un tableau d'offres de travaux.
 * @param nbOffre Le nombre d'offres dans le tableau.
 */
void selectionnerEntreprises(Offre** tOffre, int nbOffre);

/**
 * @brief Crée un tableau de tâches vide.
 *
 * Cette fonction alloue de la mémoire pour un tableau de tâches de taille `tLog`.
 * Le tableau est initialisé à NULL.
 *
 * @param tLog La taille du tableau de tâches.
 * @return Un tableau de tâches vide ou NULL en cas d'échec d'allocation.
 */
Tache** tacheVide(int tLog);

/**
 * @brief Crée une file vide.
 *
 * Cette fonction renvoie une file vide initialisée à NULL.
 *
 * @return Une file vide.
 */
ListeFile fileVide(void);

/**
 * @brief Ajoute une tâche en tête de la file.
 *
 * Cette fonction ajoute une tâche en tête de la file. La file est modifiée directement.
 *
 * @param tache Un pointeur vers la file.
 * @param tacheCourrante La tâche à enfiler.
 */
void enfilerTete(ListeFile* pTache, Tache* tacheCourrante);

/**
 * @brief Retire la dernière tâche de la file.
 *
 * Cette fonction retire la dernière tâche de la file et renvoie un pointeur vers la tâche retirée.
 * La file est modifiée directement.
 *
 * @param tache Un pointeur vers la file.
 * @return Un pointeur vers la dernière tâche retirée ou NULL si la file est vide.
 */
Tache* defiler(ListeFile * pTache);

/**
 * @brief Trie un tableau de tâches par date de début.
 *
 * Cette fonction trie un tableau de tâches en place selon la date de début croissante.
 *
 * @param tTaches Le tableau de tâches à trier.
 * @param nbrTache Le nombre de tâches dans le tableau.
 */
void trierTaches(Tache** tTaches, int nbrTache);

/**
 * @brief Effectue le traitement des tâches dans une file.
 *
 * Cette fonction prend une file de tâches, les traite et met à jour les dates de début des tâches en fonction des prédécesseurs.
 *
 * @param tache Un pointeur vers la file de tâches.
 * @param tTaches Le tableau des tâches.
 * @param nbTache Le nombre de tâches dans le tableau.
 */
void miseAJourDate(ListeFile* tache, Tache** tTaches, int nbTache);

/**
 * @brief Calcule la durée totale du projet.
 *
 * Cette fonction calcule la durée totale du projet en parcourant toutes les tâches.
 *
 * @param tTache Le tableau des tâches.
 * @param nbrTache Le nombre de tâches dans le tableau.
 */
void dureeProjet(Tache** tTache, int nbrTache);

/**
 * @brief Liste les tâches restantes après une date donnée.
 *
 * Cette fonction affiche les tâches qui n'ont pas encore débuté et dont la date de début est après la date fournie.
 *
 * @param tTache Le tableau des tâches.
 * @param nbrTache Le nombre de tâches dans le tableau.
 * @param dateDonnee La date à partir de laquelle les tâches sont listées.
 */
void tacheNonCommence(Tache** tTache, int nbrTache, int dateDonnee);

/**
 * @brief Affiche les tâches par ordre d'exécution.
 *
 * Cette fonction trie les tâches par date de début et les affiche dans un format tabulaire.
 *
 * @param tTache Le tableau des tâches.
 * @param nbrTache Le nombre de tâches dans le tableau.
 */
void ordreTache(Tache** tTache, int nbrTache);

/**
 * @brief Ajoute un successeur à une tâche.
 *
 * Cette fonction ajoute un successeur à une tâche en créant un nouveau maillon de la liste des successeurs.
 *
 * @param tache La tâche à laquelle ajouter le successeur.
 * @param nom Le nom du successeur.
 */
void ajouterSuccesseur(Tache* tache, const char* nom);

/**
 * @brief Trouve l'index d'une tâche dans un tableau par son nom.
 *
 * Cette fonction récursive recherche une tâche spécifique dans un tableau de tâches en comparant les noms.
 *
 * @param tTache Le tableau des tâches.
 * @param tMax Le nombre maximal d'éléments dans le tableau.
 * @param nom Le nom de la tâche à rechercher.
 * @param i L'indice de départ de la recherche.
 * @return L'index de la tâche si elle est trouvée, sinon -1.
 */
int trouverTache(Tache** tTache, int tMax, const char* nom, int i);

#endif // TACHE_H
