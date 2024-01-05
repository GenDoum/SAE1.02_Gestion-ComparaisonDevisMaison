//
// Created by Mathéo Hersan on 05/01/2024.
//

#include<stdio.h>
#include<stdlib.h>
#include "sauvegarde.h"


void sauvegarderDevis(Offre** tOffre, int nbDevis, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nbDevis; i++) {
        MaillonDevis* courant = tOffre[i]->ldevis;
        while (courant != NULL) {
            fprintf(fichier, "%s\n", tOffre[i]->travaux);
            fprintf(fichier, "%s\n", courant->devis.nomTache);
            fprintf(fichier, "%s\n", courant->devis.entreprise);
            // ...
            courant = courant->suivant;
        }
    }

    fclose(fichier);
}
