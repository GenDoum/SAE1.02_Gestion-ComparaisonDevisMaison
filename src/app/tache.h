#ifndef TACHE_H
#define TACHE_H
#include "affichage.h"
#include "../struct.h"

void selectionnerEntreprises(Offre** tOffre, int nbOffre);
Tache** tacheVide(int tLog);
ListeFile fileVide(void);
void enfilerTete(ListeFile* pTache, Tache* tacheCourrante);
Tache* defilerFin(ListeFile * pTache);
void trierTachesParDateDebut(Tache** tTaches, int nbrTache);
void traitementFile(ListeFile* tache, Tache** tTaches, int nbTache);
void calculerDureeProjet(Tache** tTache, int nbrTache);
void listerTachesRestantes(Tache** tTache, int nbrTache, int dateDonnee);
void afficherTachesParOrdreExecution(Tache** tTache, int nbrTache);
void ajouterSuccesseur(Tache* tache, const char* nom);
int trouverTache(Tache** tTache, int tMax, const char* nom, int i);
int chargerTache(Offre** tOffre, Tache** tTache, ListeFile * fileAttente, int nbrTache, char* nomFichier);
void libererTaches(Tache** tTache, int tMax);

#endif // TACHE_H
