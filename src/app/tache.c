#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tache.h"



// void ajouterMaillonFin( Liste *liste, Tache *tache){
//     Maillon *nouveau;
    
//     if ( (nouveau = (Maillon *)malloc(sizeof(Maillon))) == NULL){
//         perror("Erreur d'allocation de memoire");
//         exit(EXIT_FAILURE);
//     }

//     nouveau->val = tache->duree;
//     nouveau->suivant = NULL;
    
//     if (liste->fin == NULL){
//         liste->suivant = nouveau;
//         liste->fin = nouveau;
//     } else {
//         liste->fin->suivant = nouveau;
//         liste->fin = nouveau;
//     }

// }
// void supprimerPremierMaillon( Liste *liste )
// {
//     Maillon *premier = liste->suivant;
//     liste->suivant = premier->suivant;

//     free(premier);
// }


// void supprimerDernierMaillon( Liste *liste )
// {
//     // Si liste vide
//     if ( liste == NULL || liste->suivant == NULL)
//     {
//         return;
//     }

//     Maillon *dernier = liste->fin;

//     // Si la liste à qu'un seul élément
//     if ( liste->suivant == liste->fin )
//     {
//         liste->suivant = NULL;
//         liste->fin = NULL;
//     }
//     else
//     {
//         Maillon * courant = liste->suivant;
//         while (courant->suivant != dernier)
//         {
//             courant = courant->suivant;
//         }

//         courant->suivant = NULL;
//         liste->fin =courant;
//     }

//     free(dernier);
// }

// void afficherListe(Liste *liste){
//     Maillon *courant = liste->suivant;
//     while(courant != NULL){
//         printf("%d\n", courant->val);
//         courant = courant->suivant;
//     }
//     puts("");
// }


// Tache creerTache(Liste *liste)
// {
//     Tache * newTache;
    
//     if ( (newTache = (Tache*)malloc(sizeof(Tache))) == NULL )
//     {
//         perror("malloc Tache");
//         exit(-1);
//     }

//     printf("Entre le nom de la tache : ");
//     while ( (scanf("%s", newTache->tache)) != 1 )
//     {
//         fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
//         while (getchar() != '\n');
//     }

//     printf("Entre la durée :");
//     verifInt(&newTache->duree);
    

//     printf("Entre le nombre de prédecesseurs de la tache \n");
//     //fonction
    
// }


void verifInt(int *var){
    while (scanf("%d", var) != 1){
        fprintf(stderr, "\x1B[31mERREUR : Entrez un nombre valide : \x1B[0m");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');
}

void chargerPrecedences(char* nomFichier) {
    FILE* fe;

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    fclose(fe);
}

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

void creerPrecedences(char* nomFichier) {
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
