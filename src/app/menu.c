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
    printf("||\t4 : Supprimer un devis.\t\t\t\t\t\t\t\t||\n");
    printf("||\t5 : Afficher l’ensemble des devis pour un type de travaux. \t\t\t||\n");
    printf("||\t6 : Afficher le devis d’une entreprise donnée pour un type de travaux donnée.\t||\n");
    printf("||\t7 : Passer au payement.\t\t\t\t\t\t\t\t||\n");
    printf("||\t8 : Comparer Devis\t\t\t\t\t\t\t\t||\n");
    printf("||\t9 : Quitter.\t\t\t\t\t\t\t\t\t||\n");
    printf("+----------------------------------------------------------------------------------------+\n");
}


void menu_client(int *choix) {
    affiche_client();
    printf("Vous choisissez: ");
    while (scanf("%d", choix) != 1 || *choix < 0 || *choix > 9 ) {
        while (getchar() != '\n');
        fprintf(stderr, "\x1B[31mERREUR : Veuillez entrer un choix valide :\x1B[0m ");
    }
}

void global(void) {
    int choix;
    char fichierPrecedences[100] = "donnee/precedences.txt";
    char fichierDevis[100] = "donnee/devis.txt";
    int nbOffre = 0, max, tPhysique = 100, tLogPrecs = 0, *tLogNomTache = 0, tLogTaches = 0, tPhyTaches = MAX_TACHES;
    Offre** tOffre = chargement(fichierDevis, &nbOffre, &max);
    Precedences **tPrecs = chargerPrecedences(fichierPrecedences, &tPhysique, &tLogPrecs);
    Tache** taches = NULL;
    char **nomTache = NULL;
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
                taches = listerTache(tPrecs, tLogPrecs, &tLogTaches, &tPhyTaches);
                //taches = chargerTaches(tPrecs, tLogPrecs, nomTache, tLogNomTache, &tLogTaches);
                //affichPrecedence(tPrecs, tLogPrecs);
                break;
            case 5:
                afficherDevisPourType(tOffre, nbOffre);
                break;
            case 6:
                afficherDevisEntreprisePourType(tOffre, nbOffre);
                break;
            case 7:
                break;
            case 8:
                selectionnerEntreprises(tOffre, nbOffre);
                break;
            case 9:
                return;
        }
    } while (choix != 9);
}
