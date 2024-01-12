#include "chargement.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


Offre** chargement(char* nomFichier, int* nbOffre, int* max){
    int trouve, pos, i;
    int capital, duree, cout, codePostal, numero;
    char travaux[MAX_TRAVAUX], ligne[MAX_TRAVAUX], entreprise[MAX_TRAVAUX], nomRue[MAX_TRAVAUX], ville[MAX_TRAVAUX];
    Adresse adresse;
    FILE* fe;

    if ((fe = fopen(nomFichier, "r")) == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    *nbOffre = 0;
    *max = 10;
    Offre** tOffre, **tmp;

    if ((tOffre = (Offre**)malloc(*max * sizeof(Offre*))) == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, sizeof(ligne), fe) != NULL){
        sscanf(ligne, "%s", travaux);

        #ifdef DEBUG
        printf("Type de travaux lu : %s\n", travaux);  // Débogage
        #endif

        pos = rechercheDichotomique(tOffre, *nbOffre, travaux, &trouve);
        if (trouve == 0){

            #ifdef DEBUG
            printf("Offre insérée à la position %d:\n", pos);  // débogage
            printf("Type de travaux : %s\n", tOffre[pos]->travaux);  // débogage
            #endif

            #ifdef DEBUG
            // Pour vérifier les pointeurs
            printf("Adresse de l'offre à la position %d : %p\n", pos, (void *)tOffre[pos]);  // débogage
            #endif

            #ifdef DEBUG
            // Pour vérifier les offres précédentes
            for (int j = 0; j < pos; j++) {
                printf("Offre à la position %d:\n", j);  // débogage
                printf("Type de travaux : %s\n", tOffre[j]->travaux);  // débogage
            }
            #endif

            if (*nbOffre == *max){
                *max += 10;
                if ((tmp = (Offre**)realloc(tOffre, *max * sizeof(Offre*))) == NULL){
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                tOffre = tmp;
            }
            for (i = *nbOffre; i > pos; --i){
                tOffre[i] = tOffre[i - 1];
            }
            if ((tOffre[pos] = (Offre*)malloc(sizeof(Offre))) == NULL){
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(tOffre[pos]->travaux, travaux);
            tOffre[pos]->ldevis = listeVide();
            ++(*nbOffre);
        }

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%[^\n]", entreprise);

        #ifdef DEBUG
        printf("Nom de l'entreprise lu : %s\n", entreprise);  // Débogage
        #endif

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%d %[^0-9] %d %s", &numero, nomRue, &codePostal, ville);

        #ifdef DEBUG
        printf("Adresse lu : %d %s, %d %s\n", numero, nomRue, codePostal, ville);  // Débogage
        #endif

        if (fscanf(fe, "%d", &capital) != 1) {
            printf("Erreur lors de la lecture du capital.\n");
            break;
        }

        #ifdef DEBUG
        printf("Capital lu : %d\n", capital);
        #endif

        if (fscanf(fe, "%d", &duree) != 1) {
            printf("Erreur lors de la lecture de la durée.\n");
            break;
        }

        #ifdef DEBUG
        printf("Durée lu : %d\n", duree);
        #endif

        if (fscanf(fe, "%d", &cout) != 1) {
            printf("Erreur lors de la lecture du coût.\n");
            break;
        }

        #ifdef DEBUG
        printf("Coût lu : %d\n", cout);
        #endif

        adresse.numero = numero;
        strcpy(adresse.nomRue, nomRue);
        strcpy(adresse.ville, ville);
        adresse.codePostal = codePostal;

        nouveauDevis(tOffre, *nbOffre, travaux, entreprise, adresse, capital, duree, cout);
        if (fscanf(fe, "%s", travaux) == EOF) {

            #ifdef DEBUG
            printf("Fin du fichier atteinte.\n");
            break;
            #endif
        }

    }

    fclose(fe);
    return tOffre;
}

int chargerTache(Offre** tOffre, Tache** tTache, ListeFile* fileAttente, int tLogique, char* nomFichier) {
    FILE* fichier;
    char prec[30], succ[30];
    int i, iPrec;

    // Ouverture du fichier
    if ((fichier = fopen(nomFichier, "r")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Initialisation des tâches
    for (i = 0; i < tLogique; i++) {
        if ((tTache[i] = (Tache*)malloc(sizeof(Tache))) == NULL) {
            perror("malloc");

            // Libération de la mémoire allouée précédemment
            for (int k = 0; k < i; ++k) {
                free(tTache[k]);
            }

            free(tTache);
            fclose(fichier);
            return -1;
        }

        // Si l'offre est vide ou si le devis est vide, on passe à la tâche suivante
        if (tOffre[i] == NULL || tOffre[i]->ldevis == NULL) {
            continue;
        }

        // Initialisation des informations de la tâche
        strcpy(tTache[i]->tache, tOffre[i]->travaux);
        tTache[i]->duree = tOffre[i]->ldevis->devis.duree;
        tTache[i]->succ = NULL;
        tTache[i]->nbPred = 0;
        tTache[i]->traite = 0;
        tTache[i]->dateDebut = 0;
    }

    // Lecture des précédences depuis le fichier
    while (!feof(fichier)) {
        if (fscanf(fichier, "%s %s", prec, succ) != 2) {
            fprintf(stderr, "Erreur lecture des successeurs");
            exit(EXIT_FAILURE);
        }

        // Recherche des indices des tâches précédente et successeure
        iPrec = trouverTache(tTache, tLogique, prec, 0);

        if (iPrec != -1) {
            ajouterSuccesseur(tTache[iPrec], succ);

            int trouve = trouverTache(tTache, tLogique, succ, 0);

            if (trouve != -1) {
                tTache[trouve]->nbPred++;
            }
        }
    }

    // Fermeture du fichier
    fclose(fichier);

    // Initialisation de la file d'attente avec les tâches sans prédécesseurs
    for (i = 0; i < tLogique; i++) {
        if (!tTache[i]) continue;

        if (!tTache[i]->nbPred)
            enfilerTete(fileAttente, tTache[i]);
    }

    // Vérification que la file d'attente n'est pas vide
    if (fileAttente == NULL || *fileAttente == NULL) {
        fprintf(stderr, "File d'attente vide");
        exit(EXIT_FAILURE);
    }

    // Traitement de la file d'attente
    miseAJourDate(fileAttente, tTache, tLogique);

    return 0;
}
