#include <stdio.h>
#include <stdlib.h>

void creerMaillonVide(Liste *liste){
    l->suivant = NULL;
    l->fin = NULL;
}

void ajouterMaillonFin( Liste *liste, Tache *tache){
    Maillon *nouveau;
    
    if (nouveau = (Maillon *)malloc(sizeof(Maillon)) == NULL){
        perror("Erreur d'allocation de memoire");
        exit(EXIT_FAILURE);
    }
    
    nouveau->val = tache;
    nouveau-> suivant = NULL;

}
void supprimerPremierMaillon( Liste *liste )
{
    
}


void supprimerDernierMaillon( Liste *liste )
{
    liste->fin->val = NULL;
    liste->fin->suivant = NULL;
    free(liste->fin);
}