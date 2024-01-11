#ifndef SAE1_02_CHARGEMENT_H
#define SAE1_02_CHARGEMENT_H

#include "tache.h"
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

Tache** chargerTaches(Precedences **tPrecs, int tLogTabPrecedence, char **nomTache, int *tLogTabNomTache, int *tLogTaches);
Precedences **chargerPrecedences(char* nomFichier, int *tPhysique, int *nbPrec);
void compterPrecedences( Precedences **tPrecs, int tLogTabPrecedence, char **nomTache,int *tLogTabNomTache, Precedence **tPrec);
char **listerNomTache( Precedences **tPrecs, int tLogPrecs, int *tLogique, int *tPhysique);
void affichageeeeee( char **nomTache, int tLogique );

#endif //SAE1_02_CHARGEMENT_H
