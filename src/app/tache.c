#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void creerPrecedences(char* nomFichier) { // Je sais pas si c'est fait exprès masi pk pas faire en sorte que si la tache1 entré est la tache2 d'un autre alors 
// afficcher dans le fichier en mode : tache1 -> tache2 -> tache 3 ?
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

    fprintf(fe, "%s %s\n", tache1, tache2);

    fclose(fe);
}

void selectionnerEntreprises(Offre** tOffre, int nbOffre) {
    for (int i = 0; i < nbOffre; i++) {
        MaillonDevis* courant = tOffre[i]->ldevis;
        MaillonDevis* meilleurDevis = courant;
        ListeDevis aSupprimer = listeVide();

        while (courant != NULL) {
            printf("Courant : %s, %d\n", courant->devis.nomTache, courant->devis.cout);
            if (courant->devis.cout < meilleurDevis->devis.cout ||
                (courant->devis.cout == meilleurDevis->devis.cout && courant->devis.capital > meilleurDevis->devis.capital)) {
                meilleurDevis = courant;
            }
            if (courant != meilleurDevis) {
                aSupprimer = insererEnTete(aSupprimer, courant->devis.nomTache, "", (Adresse){0, "", "", 0}, 0, 0, 0);
            }
            courant = courant->suivant;
        }

        supprimerMauvaisDevis(tOffre, i, meilleurDevis);

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

    m->tacheCourrante = *tacheCourrante;
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
        tacheRetiree = &((*tache)->tacheCourrante);
        free(*tache);
        *tache = NULL;
    } else {
        tacheRetiree = &((*tache)->suivant->tacheCourrante);
        free((*tache)->suivant);
        (*tache)->suivant = NULL;
    }

    return tacheRetiree;
}

void trierTachesParDateDebut(Tache** tTaches, int nbrTache){

    for (int i = 1; i < nbrTache; i++){
        Tache* premier = tTaches[i];
        int j = i - 1;

        while (j >= 0 && tTaches[j]->dateDebut > premier->dateDebut){
            tTaches[j++] = tTaches[j];
            j--;
        }

        tTaches[j++] = premier;
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
                succTache->dateDebut = (succTache->dateDebut > cTache->dateDebut + cTache->duree) ? succTache->dateDebut : cTache->dateDebut + cTache->duree;
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

int trouverTache(Tache** tTache, int tMax, const char* nom, int i){

    if(i == tMax){
        return -1;
    }

    if (strcmp(tTache[i]->tache, nom) == 0){
        return i;
    }

    return trouverTache(tTache, tMax, nom, i + 1);
}

int chargerTache(Offre** tOffre, Tache** tTache, ListeFile * fileAttente, int nbrTache, char* nomFichier){
    FILE* fichier;
    char prec[30], succ[30];
    int i, iPrec;

    if ((fichier = fopen(nomFichier, "r")) == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < nbrTache; i++){
        if (( tTache[i] = (Tache*)malloc(sizeof(Tache))) == NULL)
        {
            perror("malloc");

            for (int k = 0; k < i; ++k){
                free(tTache[k]);
            }

            free(tTache);
            fclose(fichier);
            return -1;
        }

        // Si l'offre est vide ou si le devis est vide on passe à la tâche suivante
        if(tOffre[i] == NULL || tOffre[i]->ldevis == NULL){
            continue;
        }

        strcpy(tTache[i]->tache, tOffre[i]->travaux);
        tTache[i]->duree = tOffre[i]->ldevis->devis.duree;
        tTache[i]->succ = NULL;
        tTache[i]->nbPred = 0;
        tTache[i]->traite = 0;
        tTache[i]->dateDebut = 0;
    }

    while (!feof(fichier)){
        if(fscanf(fichier, "%s %s", prec, succ) != 2){
            fprintf(stderr, "Erreur lecture des successeurs");
            exit(EXIT_FAILURE);
        }

        iPrec = trouverTache(tTache, nbrTache, prec, 0);

        if (iPrec != -1){
            ajouterSuccesseur(tTache[iPrec], succ);

            int idxSucc = trouverTache(tTache, nbrTache, succ, 0);

            if (idxSucc != -1) {
                tTache[idxSucc]->nbPred++;
            }
        }
    }

    fclose(fichier);

    for(i = 0; i < nbrTache; i++)
    {
        if(!tTache[i]) continue;

        if(!tTache[i]->nbPred)
            enfilerTete(fileAttente, tTache[i]);
    }

    if(fileAttente == NULL || *fileAttente == NULL){
        fprintf(stderr, "File d'attente vide");
        exit(EXIT_FAILURE);
    }

    traitementFile(fileAttente, tTache, nbrTache);

    return 0;
}
