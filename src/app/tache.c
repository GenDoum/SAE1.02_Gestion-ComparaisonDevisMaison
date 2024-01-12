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

        printf(CYAN BOLD "***************************************\n" RESET);
        printf(BOLD GREEN "   OFFRE %d\n" RESET, i + 1);
        printf(CYAN BOLD "***************************************\n" RESET);

        while (courant != NULL) {

#ifdef DEBUG
            // Débogage : Affichage des informations courantes
            printf("\t%s - Coût : %d\n", courant->devis.nomTache, courant->devis.cout);
#endif

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
        printf("\n%sMeilleure entreprise sélectionnée :\n" RESET, BOLD);
        printf("\t%sTâche : %s %s\n", UNDERLINE RED, RESET, meilleurDevis->devis.nomTache);
        printf("\t%sEntreprise : %s %s\n", UNDERLINE RED, RESET, meilleurDevis->devis.entreprise);
        printf("\t%sCoût : %s %d €\n", UNDERLINE RED, RESET, meilleurDevis->devis.cout);
        printf("\t%sCapital : %s %d €\n", UNDERLINE RED, RESET, meilleurDevis->devis.capital);
    }
}

ListeFile fileVide(void){
    return NULL;
}

Tache** tacheVide(int tLog){
    Tache** tache;

    if((tache = (Tache**)malloc(tLog * sizeof(Tache*))) == NULL){
        perror("malloc");
        return NULL;
    }

    return tache;
}

void enfilerTete(ListeFile* tache, Tache* tacheEnfiler){
    ListeFile m;

    if(!tacheEnfiler){
        return;
    }

    if ((m = (ListeFile)malloc(sizeof(File))) == NULL){
        perror("malloc");
        return;
    }

    m->tacheCourante = *tacheEnfiler;
    m->suivant = *tache;
    *tache = m;

#ifdef DEBUG
    printf("Tâche enfilée : %s, Date de début : %d\n", tacheEnfiler->tache, tacheEnfiler->dateDebut);
#endif
}

Tache* defiler(ListeFile* tache) {
    Tache* tacheDefiler;

    if (*tache == NULL){
        return NULL;
    }

    while ((*tache)->suivant != NULL && (*tache)->suivant->suivant != NULL) {
        tache = &((*tache)->suivant);
    }

    if ((*tache)->suivant == NULL) {
        tacheDefiler = &((*tache)->tacheCourante);
        free(*tache);
        *tache = NULL;
    } else {
        tacheDefiler = &((*tache)->suivant->tacheCourante);
        free((*tache)->suivant);
        (*tache)->suivant = NULL;
    }

    return tacheDefiler;
}

void trierTaches(Tache** tTaches, int tLogique){
    Tache* premier;
    int j;

#ifdef DEBUG
    printf("Tri des tâches\n");
#endif

    for (int i = 1; i < tLogique; i++){

#ifdef DEBUG
        printf("i = %d\n", i);
#endif

        premier = tTaches[i];
        j = i - 1;

        while (j >= 0 && tTaches[j]->dateDebut > premier->dateDebut){
            tTaches[j+1] = tTaches[j];
            j--;
        }

        tTaches[j+1] = premier;
    }
}

void ordreTache(Tache** tTache, int tLogique){
    trierTaches(tTache, tLogique);

    printf("+----------------------------------------------+\n");
    printf(" Tâche\t\t\tDate de début\n");
    printf("+----------------------------------------------+\n");

    for (int i = 0; i < tLogique; i++) {
        if (tTache[i] != NULL) {
            printf("| %-20s\t| %-20d |\n", tTache[i]->tache, tTache[i]->dateDebut);
        }
    }

    printf("+----------------------------------------------+\n");
}

int trouverTache(Tache** tTache, int tPhysique, char* nomTache, int i) {
    // Cas de base : atteint la fin du tableau
    if (i == tPhysique) {
        return -1;
    }

    // Comparaison des noms
    if (strcmp(tTache[i]->tache, nomTache) == 0) {
        return i;
    }

    // Appel récursif avec l'indice suivant
    return trouverTache(tTache, tPhysique, nomTache, i + 1);
}

void miseAJourDate(ListeFile* tache, Tache** tTaches, int nbTache){
    Tache* cTache, *succTache;
    ListeSuccesseur* succ;
    int indiceSucc;

    while (*tache != NULL){
        cTache = defiler(tache);

        succ = cTache->succ;
        while (succ != NULL){
            indiceSucc = trouverTache(tTaches, nbTache, succ->nomTache, 0);
            if (indiceSucc != -1){
                succTache = tTaches[indiceSucc];

                if (succTache->dateDebut > cTache->dateDebut + cTache->duree) {
                    succTache->dateDebut = succTache->dateDebut;
                } else {
                    succTache->dateDebut = cTache->dateDebut + cTache->duree;
                }

                succTache->nbPred--;

                if (!succTache->nbPred) {
                    enfilerTete(tache, succTache);
                }

#ifdef DEBUG
                printf("Mise à jour de la date de la tâche : %s, Nouvelle date de début : %d\n", succTache->tache, succTache->dateDebut);
#endif
            }

            succ = succ->suivant;
        }
    }
}

void dureeProjet(Tache** tTache, int tLogique){
    int dureeProjet = 0, finTache;

    for (int i = 0; i < tLogique; i++){
        if (tTache[i] != NULL){
            finTache = tTache[i]->dateDebut + tTache[i]->duree;
            if (finTache > dureeProjet) {
                dureeProjet = finTache;
            }
        }
    }

    printf("Ce projet durera %d jours.\n", dureeProjet);
}

void tacheNonCommence(Tache** tTache, int tLogique, int date){
    printf("\nTâches restantes après la date %d:\n\n", date);

    for (int i = 0; i < tLogique; i++){
        if (tTache[i] != NULL && tTache[i]->dateDebut > date) {
            printf("Tâche: %s\n", tTache[i]->tache);
            printf("Date de début: %d\n\n", tTache[i]->dateDebut);
        }
    }
}

void ajouterSuccesseur(Tache* tache, char* nomSucc){
    ListeSucc succ;

    if ((succ = (ListeSucc)malloc(sizeof(ListeSuccesseur))) == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(succ->nomTache, nomSucc);
    succ->suivant = tache->succ;
    tache->succ = succ;

#ifdef DEBUG
    printf("Successeur ajouté à la tâche %s : %s\n", tache->tache, nomSucc);
#endif
}
