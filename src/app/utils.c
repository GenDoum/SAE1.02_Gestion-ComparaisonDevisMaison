//
// Created by Mathéo Hersan on 05/01/2024.
//

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ListeDevis listeVide(void){
    ListeDevis l;
    l = NULL;
    return l;
}

ListeDevis insererEnTete(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout){
    MaillonDevis *nouveauMaillon = (MaillonDevis*)malloc(sizeof(MaillonDevis));
    if (nouveauMaillon == NULL){
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(nouveauMaillon->devis.nomTache, nomTache);
    strcpy(nouveauMaillon->devis.entreprise, entreprise);
    nouveauMaillon->devis.adresse = adresse;
    nouveauMaillon->devis.capital = capital;
    nouveauMaillon->devis.duree = duree;
    nouveauMaillon->devis.cout = cout;

    nouveauMaillon->suivant = l;
    return nouveauMaillon;
}

ListeDevis insertionCroissante(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout){
    if (l == NULL){
        return insererEnTete(l, nomTache, entreprise, adresse, capital, duree, cout);
    }
    if (strcmp(nomTache, l->devis.nomTache) < 0){
        return insererEnTete(l, nomTache, entreprise, adresse, capital, duree, cout);
    }
    l->suivant = insertionCroissante(l->suivant, nomTache, entreprise, adresse, capital, duree, cout);
    return l;
}


int appartient(ListeDevis l, char* nomTache){
    if (l == NULL){
        return 0;
    }

    if (strcmp(nomTache, l->devis.nomTache) < 0){
        return 0;
    }

    if (strcmp(nomTache, l->devis.nomTache) == 0){
        return 1;
    }
    return appartient(l->suivant, nomTache);
}

void quickSort(Offre** tOffre, int tLogique){
    int i = 0, j = tLogique - 2;
    Offre tmp; Offre* pivot = tOffre[tLogique - 1];

    if (tLogique <= 1) return;

    while (i <= j){
        while (i < tLogique - 1 && strcmp(tOffre[i]->travaux, pivot->travaux) < 0) ++i;

        while (j >= 0 && strcmp(tOffre[j]->travaux, pivot->travaux) > 0) --j;

        if (i < j){
            tmp = *tOffre[i];
            *tOffre[i] = *tOffre[j];
            *tOffre[j] = tmp;
        }
    }

    tOffre[tLogique - 1] = tOffre[i]; tOffre[i] = pivot;
    quickSort(tOffre, i); quickSort(tOffre + i + 1, tLogique - i - 1);
}

int rechercheDichotomique(Offre** tOffre, int tLogique, char* nomTache, int* trouve){
    int debut = 0, fin = tLogique - 1, milieu;

    printf("Recherche de la tâche : %s\n", nomTache); // Débogage

    while (debut <= fin){
        milieu = (debut + fin) / 2;
//        printf("Milieu : %d\n", milieu); // Débogage

        if (strcmp(nomTache, tOffre[milieu]->travaux) == 0){
            *trouve = 1;
            printf("Tâche trouvée à la position : %d\n", milieu); // Débogage
            return milieu;
        }
        if (strcmp(nomTache, tOffre[milieu]->travaux) < 0){
            fin = milieu - 1;
        }
        else{
            debut = milieu + 1;
        }
    }
    *trouve = 0;
    printf("Tâche non trouvée. Insérer à la position : %d\n", debut);  // Débogage
    return debut;
}

void nouveauDevis(Offre** tOffre, int nbDevis, char* nomTache, char* entreprise, Adresse adresse, int capital, int duree, int cout){
    int trouve, pos;

    printf("Appel à nouveauDevis avec : %s, %s, %d, %d, %d, %d\n", nomTache, entreprise, capital, duree, cout, nbDevis);  // Débogage


    pos = rechercheDichotomique(tOffre, nbDevis, nomTache, &trouve);

    // Toujours insérer la tâche, qu'elle soit trouvée ou non
    tOffre[pos]->ldevis = insertionCroissante(tOffre[pos]->ldevis, nomTache, entreprise, adresse, capital, duree, cout);

}



bool vide(ListeDevis l){
    if (l == NULL){
        return true;
    }
    return false;
}

int len(ListeDevis l){
    int cpt = 0;
    while(!vide(l)){
        ++cpt;
        l = l->suivant;
    }
    return cpt;
}

void supprimerMauvaisDevis(Offre** tOffre, int i, MaillonDevis* meilleurDevis) {
    MaillonDevis* courant = tOffre[i]->ldevis;
    MaillonDevis* prec = NULL;
    while (courant != NULL) {
        if (courant != meilleurDevis) {
            if (prec == NULL) {
                tOffre[i]->ldevis = courant->suivant;
            } else {
                prec->suivant = courant->suivant;
            }
            free(courant);
            if (prec == NULL) {
                courant = tOffre[i]->ldevis;
            } else {
                courant = prec->suivant;
            }
        } else {
            prec = courant;
            courant = courant->suivant;
        }
    }
}

