#include <stdio.h>
#include "menu.h"
#include "tache.h"
#include "chargement.h"
#include "affichage.h"

void affiche_client(void) {
    printf("\n");
    printf("+-------------+\n");
    printf("|| Bonjour ! ||\n");
    printf("+-------------+\n");
    printf("\n");
    printf("+----------------------------------------------------------------------------------------+\n");
    printf("|| Que voulez-vous faire ?\t\t\t\t\t\t\t\t||\n");
    printf("||\t1 : Afficher les précédences.\t\t\t\t\t\t\t||\n");
    printf("||\t2 : Ajouter une précédence.\t\t\t\t\t\t\t||\n");
    printf("||\t3 : Afficher les devis.   \t\t\t\t\t\t\t||\n");
    printf("||\t4 : Ajouter un devis. \t\t\t\t\t\t\t\t||\n");
    printf("||\t5 : Afficher l’ensemble des devis pour un type de travaux. \t\t\t||\n");
    printf("||\t6 : Afficher le devis d’une entreprise donnée pour un type de travaux donnée.\t||\n");
    printf("||\t7 : Passer au payement.\t\t\t\t\t\t\t\t||\n");
    printf("||\t9 : Quitter.\t\t\t\t\t\t\t\t\t||\n");
    printf("+----------------------------------------------------------------------------------------+\n");
}

void menu_client(int *choix) {
    affiche_client();
    printf("Vous choisissez: ");
    while (scanf("%d", choix) != 1 || *choix < 0 || *choix > 9 || (*choix > 7 && *choix < 9)) {
        while (getchar() != '\n');
        fprintf(stderr, "\x1B[31mERREUR : Veuillez entrer un choix valide :\x1B[0m ");
    }
}

void global(void) {
    int choix;
    char fichierPrecedences[100] = "donnee/precedences.txt";
    char fichierDevis[100] = "donnee/devis.txt";
    Offre *tOffre[10];
    int nbOffres = 0;
    nbOffres = chargerDevis(fichierDevis, tOffre);

    printf("Nombre de devis chargés : %d\n", nbOffres);
    do {
        menu_client(&choix);

        switch (choix) {
            case 1:
                afficherPrecedences(fichierPrecedences);
                break;
            case 2:
                creerPrecedences(fichierPrecedences);
                break;
            case 3:
                //ajouterMaillonDevisFin(&listeDevis);
                break;
            case 4:
                afficherOffres(tOffre, nbOffres);
                break;
            case 5:
                afficherDevisParTypeTravaux(tOffre, nbOffres);
                break;
            case 6:
                afficherDevisEntrepriseType(tOffre, nbOffres);
                break;
            case 7:
                break;
            case 9:
                return;
        }
    } while (choix != 9);
}
