#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tache.h"
#include "affichage.h"
#include "utils.h"

void verifInt(int *var){
    while (scanf("%d", var) != 1){
        fprintf(stderr, "\x1B[31mERREUR : Entrez un nombre valide : \x1B[0m");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');
}



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