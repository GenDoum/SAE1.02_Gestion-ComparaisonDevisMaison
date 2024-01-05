//
// Created by Mathéo Hersan on 05/01/2024.
//

#ifndef SAE1_02_UTILS_H
#define SAE1_02_UTILS_H
#include "tache.h"

ListeDevis listeVide(void);
ListeDevis insererEnTete(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout);
ListeDevis insertionCroissante(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout);
void quickSort(Offre** tOffre, int tLogique);
void nouveauDevis(Offre** tOffre, int nbDevis, char* nomTache, char* entreprise, Adresse adresse, int capital, int duree, int cout);
int appartient(ListeDevis l, char* nomTache);
int rechercheDichotomique(Offre** tOffre, int tLogique, char* nomTache, int* trouve);
bool vide(ListeDevis l);
int len(ListeDevis l);

#endif //SAE1_02_UTILS_H
