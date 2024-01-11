#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void creerPrecedences(char* nomFichier) {
    FILE* fe;
    char tache1[21], tache2[21];

    if ( (fe = fopen(nomFichier, "a")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    printf("Entrez le nom de la tache 1 : ");
    while ( (scanf("%s", tache1)) != 1 ) {
        fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
        while (getchar() != '\n');
    }

    printf("Entrez le nom de la tache 2 : ");
    while ( (scanf("%s", tache2)) != 1 ) {
        fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
        while (getchar() != '\n');
    }

    fprintf(fe, "\n%s %s", tache1, tache2);

    fclose(fe);
}

void selectionnerEntreprises(Offre** tOffre, int nbOffre) {
    for (int i = 0; i < nbOffre; i++) {
        MaillonDevis* courant = tOffre[i]->ldevis;
        MaillonDevis* meilleurDevis = courant;
        ListeDevis aSupprimer = listeVide();

        while (courant != NULL) {
            // Débogage : Affichage des informations courantes
            printf("Courant : %s, %d\n", courant->devis.nomTache, courant->devis.cout);

            // Comparaison pour trouver la meilleure entreprise
            if (courant->devis.cout < meilleurDevis->devis.cout ||
                (courant->devis.cout == meilleurDevis->devis.cout && courant->devis.capital > meilleurDevis->devis.capital)) {
                meilleurDevis = courant;
            }

            // Ajout des entreprises moins avantageuses à la liste à supprimer
            if (courant != meilleurDevis) {
                aSupprimer = insererEnTete(aSupprimer, courant->devis.nomTache, "", (Adresse){0, "", "", 0}, 0, 0, 0);
            }
            courant = courant->suivant;
        }

        // Suppression des mauvais devis
        supprimerMauvaisDevis(tOffre, i, meilleurDevis);

        // Affichage des informations de la meilleure entreprise sélectionnée
        printf("Tâche : %s\nEntreprise : %s\nCoût : %d\nCapital : %d\n", meilleurDevis->devis.nomTache, meilleurDevis->devis.entreprise, meilleurDevis->devis.cout, meilleurDevis->devis.capital);
    }
}

// ============================================================================================== //

Tache** tacheVide(int tLog){

    Tache** nouvelleTache = (Tache**)malloc(tLog * sizeof(Tache*));
    if(nouvelleTache == NULL){
        perror("malloc");
        return NULL;
    }

    return nouvelleTache;
}

ListeFile fileVide(void){
    return NULL;
}

void enfilerTete(ListeFile* tache, Tache* tacheCourrante){

    if(!tacheCourrante) return;

    ListeFile m;
    if ((m = (ListeFile)malloc(sizeof(File))) == NULL){
        perror("malloc");
        return;
    }

    m->tacheCourante = *tacheCourrante;
    m->suivant = *tache;
    *tache = m;
}

Tache* defilerFin(ListeFile* tache) {

    if (*tache == NULL) return NULL;

    while ((*tache)->suivant != NULL && (*tache)->suivant->suivant != NULL) {
        tache = &((*tache)->suivant);
    }

    Tache* tacheRetiree;

    if ((*tache)->suivant == NULL) {
        tacheRetiree = &((*tache)->tacheCourante);
        free(*tache);
        *tache = NULL;
    } else {
        tacheRetiree = &((*tache)->suivant->tacheCourante);
        free((*tache)->suivant);
        (*tache)->suivant = NULL;
    }

    return tacheRetiree;
}

void trierTachesParDateDebut(Tache** tTaches, int nbrTache){

#ifdef DEBUG
    printf("nbrTache : %d\n", nbrTache);
#endif
    for (int i = 1; i < nbrTache; i++){

#ifdef DEBUG
        printf("i = %d\n", i);
#endif
        Tache* premier = tTaches[i];
        int j = i - 1;

        while (j >= 0 && tTaches[j]->dateDebut > premier->dateDebut){
            tTaches[j+1] = tTaches[j]; 
            j--;
        }

        tTaches[j+1] = premier;
    }
}

void traitementFile(ListeFile* tache, Tache** tTaches, int nbTache){

    while (*tache != NULL){
        Tache* cTache = defilerFin(tache);

        ListeSuccesseur* succ = cTache->succ;
        while (succ != NULL){
            int idxSucc = trouverTache(tTaches, nbTache, succ->nomTache, 0);
            if (idxSucc != -1){
                Tache* succTache = tTaches[idxSucc];
                
                if (succTache->dateDebut > cTache->dateDebut + cTache->duree) {
                    succTache->dateDebut = succTache->dateDebut;
                } else {
                    succTache->dateDebut = cTache->dateDebut + cTache->duree;
                }

                succTache->nbPred--;

                if (!succTache->nbPred) {
                    enfilerTete(tache, succTache);
                }
            }

            succ = succ->suivant;
        }
    }
}

void calculerDureeProjet(Tache** tTache, int nbrTache){

    int dureeProjet = 0;

    for (int i = 0; i < nbrTache; i++){
        if (tTache[i] != NULL){
            int finTache = tTache[i]->dateDebut + tTache[i]->duree;
            if (finTache > dureeProjet) {
                dureeProjet = finTache;
            }
        }
    }

    printf("\nLe projet durera %d jours.", dureeProjet);
}

void listerTachesRestantes(Tache** tTache, int nbrTache, int dateDonnee){

    printf("\nTâches restantes après la date %d:\n\n", dateDonnee);

    for (int i = 0; i < nbrTache; i++){
        if (tTache[i] != NULL && tTache[i]->dateDebut > dateDonnee) {
            printf("Tâche: %s | Date de début: %d\n", tTache[i]->tache, tTache[i]->dateDebut);
        }
    }
}

void afficherTachesParOrdreExecution(Tache** tTache, int nbrTache){
    trierTachesParDateDebut(tTache, nbrTache);

    printf("+----------------------------------------------+\n");
    printf(" Tâche\t\t\tDate de début\n");
    printf("+----------------------------------------------+\n");

    for (int i = 0; i < nbrTache; i++) {
        if (tTache[i] != NULL) {
            printf("| %-20s\t| %-20d |\n", tTache[i]->tache, tTache[i]->dateDebut);
        }
    }

    printf("+----------------------------------------------+\n");
}

void ajouterSuccesseur(Tache* tache, const char* nom){
    ListeSucc nSucc;

    if ((nSucc = (ListeSucc)malloc(sizeof(ListeSuccesseur))) == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(nSucc->nomTache, nom);
    nSucc->suivant = tache->succ;
    tache->succ = nSucc;
}

int trouverTache(Tache** tTache, int tMax, const char* nom, int i) {
    // Cas de base : atteint la fin du tableau
    if (i == tMax) {
        return -1;
    }

    // Comparaison des noms
    if (strcmp(tTache[i]->tache, nom) == 0) {
        return i;
    }

    // Appel récursif avec l'indice suivant
    return trouverTache(tTache, tMax, nom, i + 1);
}
