#include <stdio.h>
#include <stdlib.h>
#include "tache.h"


void creerMaillonVide(Liste *liste){
    liste->suivant = NULL;
    liste->fin = NULL;
}


void ajouterMaillonFin( Liste *liste, Tache *tache){
    Maillon *nouveau;
    
    if ( (nouveau = (Maillon *)malloc(sizeof(Maillon))) == NULL){
        perror("Erreur d'allocation de memoire");
        exit(EXIT_FAILURE);
    }

    nouveau->val = tache->duree;
    nouveau->suivant = NULL;
    
    if (liste->fin == NULL){
        liste->suivant = nouveau;
        liste->fin = nouveau;
    } else {
        liste->fin->suivant = nouveau;
        liste->fin = nouveau;
    }

}
void supprimerPremierMaillon( Liste *liste )
{
    Maillon *premier = liste->suivant;
    liste->suivant = premier->suivant;

    free(premier);
}


void supprimerDernierMaillon( Liste *liste )
{
    // Si liste vide
    if ( liste == NULL || liste->suivant == NULL)
    {
        return;
    }

    Maillon *dernier = liste->fin;

    // Si la liste à qu'un seul élément
    if ( liste->suivant == liste->fin )
    {
        liste->suivant = NULL;
        liste->fin = NULL;
    }
    else
    {
        Maillon * courant = liste->suivant;
        while (courant->suivant != dernier)
        {
            courant = courant->suivant;
        }

        courant->suivant = NULL;
        liste->fin =courant;
    }

    free(dernier);
}

void afficherListe(Liste *liste){
    Maillon *courant = liste->suivant;
    while(courant != NULL){
        printf("%d\n", courant->val);
        courant = courant->suivant;
    }
    puts("");
}

void verifInt(int *var){
    while (scanf("%d", var) != 1){
        fprintf(stderr, "\x1B[31mERREUR : Entrez un nombre valide : \x1B[0m");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');
}

Tache creerTache(Liste *liste)
{
    Tache * newTache;
    
    if ( (newTache = (Tache*)malloc(sizeof(Tache))) == NULL )
    {
        perror("malloc Tache");
        exit(-1);
    }

    printf("Entre le nom de la tache : ");
    while ( (scanf("%s", newTache->tache)) != 1 )
    {
        fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
        while (getchar() != '\n');
    }

    printf("Entre la durée :");
    verifInt(&newTache->duree);
    

    printf("Entre le nombre de prédecesseurs de la tache \n");
    //fonction
    
}
