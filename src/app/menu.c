#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "tache.h"

void affiche_client(void) {
    printf("\n");
    printf("+-------------+\n");
    printf("|| Bonjour ! ||\n");
    printf("+-------------+\n");
    printf("\n");
    printf("+----------------------------------------------------------------+\n");
    printf("|| Que voulez-vous faire ?\t\t\t\t\t||\n");
    printf("||\t1 : Afficher les précédences.\t \t\t\t||\n");
    printf("||\t2 : Ajouter une précédence.\t\t\t\t||\n");
    printf("||\t3 : Afficher les devis.   \t\t\t\t||\n");
    printf("||\t4 : Supprimer un article du panier. \t\t\t||\n");
    printf("||\t5 : Modifier la quantité d'un article du panier. \t||\n");
    printf("||\t6 : Réinitialiser le panier.\t\t\t\t||\n");
    printf("||\t7 : Passer au payement.\t\t\t\t\t||\n");
    printf("||\t9 : Quitter.\t\t\t\t\t\t||\n");
    printf("+----------------------------------------------------------------+\n");
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
    Offre offre;
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
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 9:
                return;
        }
    } while (choix != 9);
}
