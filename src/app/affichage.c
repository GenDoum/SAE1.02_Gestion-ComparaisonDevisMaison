//
// Created by Mathéo Hersan on 03/01/2024.
//

#include "affichage.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void afficherPrecedences(char* nomFichier) {
    FILE* fe;
    char tache1[21], tache2[21];

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    while (fscanf(fe, "%s%s\n", tache1, tache2) == 2) {
        printf("%s -> %s\n", tache1, tache2);
    }

    fclose(fe);
}

void afficher(Offre** tOffre, int nbOffre) {
    for (int i = 0; i < nbOffre; i++) {
        printf("Type de travaux : %s\n", tOffre[i]->travaux);
        afficherListeDevis(tOffre[i]->ldevis, i + 1);
        printf("\n");
    }
}

void afficherListeDevis(ListeDevis l, int nbDevis) {
    if (l == NULL) {
        printf("Liste vide.\n");
        return;
    }

    while (l != NULL) {
        printf("=== Offre n°%d ===\n", nbDevis);
        printf("Nom de la tâche : %s\n", l->devis.nomTache);
        printf("Nom de l'entreprise : %s\n", l->devis.entreprise);
        printf("Adresse : %d %s, %d %s\n", l->devis.adresse.numero, l->devis.adresse.nomRue, l->devis.adresse.codePostal, l->devis.adresse.ville);
        printf("Capital : %d\n", l->devis.capital);
        printf("Durée : %d\n", l->devis.duree);
        printf("Coût : %d\n", l->devis.cout);
        printf("\n");
        l = l->suivant;
    }
}

void afficherDevisPourType(Offre** tOffre, int nbOffre) {
    int trouve = 0;
    char typeTravaux[MAX_TRAVAUX];

    printf("Saisir le type de travaux : ");
    scanf("%s%*c", typeTravaux);

    for (int i = 0; i < nbOffre; i++) {
        if (strcmp(tOffre[i]->travaux, typeTravaux) == 0) {
            trouve = 1;
            printf("Type de travaux : %s\n", tOffre[i]->travaux);
            afficherListeDevis(tOffre[i]->ldevis, i + 1);
            printf("\n");
            break;
        }
    }
    if (!trouve) {
        printf("Aucun devis trouvé pour le type de travaux : %s\n", typeTravaux);
    }
}

void afficherDevisEntreprisePourType(Offre** tOffre, int nbOffre) {
    int trouve = 0;
    char typeTravaux[MAX_TRAVAUX], nomEntreprise[MAX_TRAVAUX];

    printf("Saisir le type de travaux : ");
    scanf("%s%*c", typeTravaux);
    printf("Saisir le nom de l'entreprise : ");
    scanf("%s%*c", nomEntreprise);

    for (int i = 0; i < nbOffre; i++) {
        if (strcmp(tOffre[i]->travaux, typeTravaux) == 0) {
            ListeDevis ldevis = tOffre[i]->ldevis;
            while (ldevis != NULL) {
                if (strcmp(ldevis->devis.entreprise, nomEntreprise) == 0) {
                    trouve = 1;
                    printf("Type de travaux : %s\n", tOffre[i]->travaux);
                    afficherListeDevis(ldevis, i + 1);
                    printf("\n");
                    break;
                }
                ldevis = ldevis->suivant;
            }
        }
    }
    if (!trouve) {
        printf("Aucun devis trouvé pour l'entreprise : %s et le type de travaux : %s\n", nomEntreprise, typeTravaux);
    }
}