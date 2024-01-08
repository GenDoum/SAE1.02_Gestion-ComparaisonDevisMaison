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

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define RED "\033[31m"
#define GREEN "\033[92m"
#define PURPLE "\033[35m"  // Nouvelle couleur pour le violet
#define BLUE "\033[94m"
#define MAGENTA "\033[95m"
#define CYAN "\033[96m"

void afficher(Offre** tOffre, int nbOffre) {
    for (int i = 0; i < nbOffre; i++) {
        printf(CYAN BOLD "========================================\n" RESET);
        printf(BOLD GREEN "   OFFRE %d\n" RESET, i + 1);
        printf(CYAN BOLD "----------------------------------------\n" RESET);
        printf(RED "   Type de travaux : %s\n" RESET, tOffre[i]->travaux);
        printf(CYAN BOLD "----------------------------------------\n" RESET);
        afficherListeDevis(tOffre[i]->ldevis, i + 1);
        printf(CYAN BOLD "========================================\n\n" RESET);
    }
}

void afficherListeDevis(ListeDevis l, int nbDevis) {
    if (l == NULL) {
        printf(RED BOLD "Aucun devis disponible.\n" RESET);
        return;
    }

    int count = 1;
    while (l != NULL) {
        printf(BOLD GREEN "   DEVIS %d\n" RESET, count);

        // Affichage des informations avec soulignement
        printf("\t%sNom de la tâche :%s %s\n", UNDERLINE RED, RESET, l->devis.nomTache);
        printf("\t%sEntreprise :%s %s\n", UNDERLINE RED, RESET, l->devis.entreprise);
        printf("\t%sAdresse :%s %d %s %s\n", UNDERLINE RED, RESET, l->devis.adresse.numero, l->devis.adresse.nomRue, l->devis.adresse.ville);
        printf("\t%sCapital :%s %d\n", UNDERLINE RED, RESET, l->devis.capital);
        printf("\t%sDurée :%s %d\n", UNDERLINE RED, RESET, l->devis.duree);
        printf("\t%sCoût :%s %d €\n", UNDERLINE RED, RESET, l->devis.cout);

        printf(CYAN BOLD "----------------------------------------\n" RESET);

        l = l->suivant;
        count++;
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
    scanf("%s", typeTravaux);

    while ((getchar()) != '\n');

    printf("Saisir le nom de l'entreprise : ");
    scanf("%[^\n]", nomEntreprise);

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
