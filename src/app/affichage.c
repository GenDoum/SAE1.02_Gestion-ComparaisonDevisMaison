//
// Created by Mathéo Hersan on 03/01/2024.
//

#include "affichage.h"

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

void afficherOffres(Offre** tOffre, int nbOffres) {
    printf("Liste des offres :\n");
    for (int i = 0; i < nbOffres; i++) {
        printf("=== Offre n°%d ===\n", i + 1);
        printf("Type de travaux : %s\n", tOffre[i]->travaux);

        MaillonDevis* courant = tOffre[i]->ldevis;
        while (courant != NULL) {
            printf("Nom de la tâche : %s\n", courant->devis.nomTache);
            printf("Nom de l'entreprise : %s\n", courant->devis.entreprise);
            printf("Adresse : %d %s, %d %s\n", courant->devis.adresse.numero, courant->devis.adresse.nomRue, courant->devis.adresse.codePostal, courant->devis.adresse.ville);
            printf("Capital : %d\n", courant->devis.capital);
            printf("Durée : %d\n", courant->devis.duree);
            printf("Coût : %d\n", courant->devis.cout);
            courant = courant->suivant;
        }

        printf("\n");
    }
}

void afficherUnTravaux(Offre* offre) {
    printf("Type de travaux : %s\n", offre->travaux);
    MaillonDevis* courant = offre->ldevis;
    while (courant != NULL) {
        printf("Nom de la tâche : %s\n", courant->devis.nomTache);
        printf("Nom de l'entreprise : %s\n", courant->devis.entreprise);
        printf("Adresse : %d %s, %d %s\n", courant->devis.adresse.numero, courant->devis.adresse.nomRue, courant->devis.adresse.codePostal, courant->devis.adresse.ville);
        printf("Capital : %d\n", courant->devis.capital);
        printf("Durée : %d\n", courant->devis.duree);
        printf("Coût : %d\n", courant->devis.cout);
        puts("");
        courant = courant->suivant;
    }
}

void afficherDevisParTypeTravaux(Offre** tOffre, int nbDevis) {
    char typeTravaux[MAX_LIGNE];
    bool devisTrouve = false;
    printf("Veuillez entrer le type de travaux pour afficher les devis correspondants : ");
    scanf("%s", typeTravaux);

    for (int i = 0; i < nbDevis; i++) {
        if (strcmp(tOffre[i]->travaux, typeTravaux) == 0) {
            MaillonDevis* courant = tOffre[i]->ldevis;
            while (courant != NULL) {
                printf("=== Offre n°%d ===\n", i + 1);
                afficherUnTravaux(tOffre[i]);
                courant = courant->suivant;
            }
            devisTrouve = true;
        }
    }

    if (!devisTrouve) {
        printf("Aucun devis pour le type de travaux.\n");
    }
}


void afficherDevisEntrepriseType(Offre** tOffre, int nbDevis) {
    char typeTravaux[MAX_LIGNE], nomEntreprise[MAX_LIGNE];
    bool devisTrouve = false;
    printf("Veuillez entrer le type de travaux pour afficher les devis correspondants : ");
    scanf("%s", typeTravaux);

    while ((getchar()) != '\n');

    printf("Veuillez entrer le nom de l'entreprise pour afficher les devis correspondants : ");
    scanf("%[^\n]", nomEntreprise);

    for (int i = 0; i < nbDevis; i++) {
        if (strcmp(tOffre[i]->travaux, typeTravaux) == 0) {
            MaillonDevis* courant = tOffre[i]->ldevis;
            while (courant != NULL) {
                if (strcmp(courant->devis.entreprise, nomEntreprise) == 0) {
                    printf("=== Offre n°%d ===\n", i + 1);
                    afficherUnTravaux(tOffre[i]);
                    devisTrouve = true;
                }
                courant = courant->suivant;
            }
        }
    }

    if (!devisTrouve) {
        printf("Aucun devis pour le type de travaux et l'entreprise.\n");
    }
}