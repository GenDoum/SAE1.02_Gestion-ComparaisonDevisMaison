#include <stdio.h>
#include "menu.h"
#include "chargement.h"

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
    printf("||\t4 : Afficher l’ensemble des devis pour un type de travaux. \t\t\t||\n");
    printf("||\t5 : Afficher le devis d’une entreprise donnée pour un type de travaux donnée.\t||\n");
    printf("||\t6 : Sélectionne les meilleures entreprises pour chaque type de travaux.\t\t||\n");
    printf("||\t7 : Afficher les informations sur le projet.\t\t\t\t\t||\n");
    printf("||\t8 : Quitter.\t\t\t\t\t\t\t\t\t||\n");
    printf("+----------------------------------------------------------------------------------------+\n");
}

void menu_client(int *choix) {
    affiche_client();
    printf("Vous choisissez: ");
    while (scanf("%d", choix) != 1 || *choix < 0 || *choix > 8 ) {
        while (getchar() != '\n');
        fprintf(stderr, "\x1B[31mERREUR : Veuillez entrer un choix valide :\x1B[0m ");
    }
}

void global(void) {
    int choix;
    char fichierPrecedences[100] = "donnee/precedences.txt";
    char fichierDevis[100] = "donnee/devis.txt";
    int nbOffre = 0, max;
    Offre** tOffre = chargement(fichierDevis, &nbOffre, &max);
    Tache** tabTaches = tacheVide(nbOffre);
    ListeFile file = fileVide();

    int status = chargerTache(tOffre, tabTaches, &file, nbOffre, fichierPrecedences);
    if (status != 0) {
        fprintf(stderr, "Erreur lors du chargement des tâches.\n");
        return;
    }

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
                afficher(tOffre, nbOffre);
                break;
            case 4:
                afficherDevisPourType(tOffre, nbOffre);
                break;
            case 5:
                afficherDevisEntreprisePourType(tOffre, nbOffre);
                break;
            case 6:
                selectionnerEntreprises(tOffre, nbOffre);
                break;
            case 7:
                afficherTachesParOrdreExecution(tabTaches, nbOffre);
                calculerDureeProjet(tabTaches, nbOffre);
                listerTachesRestantes(tabTaches, nbOffre, 0);
                break;
            case 8:
                break;
        }
    } while (choix != 8);
}
