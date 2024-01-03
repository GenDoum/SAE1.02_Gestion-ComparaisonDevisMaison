#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tache.h"

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

void saisieMaillon( char *nomTache, char *entreprise, Adresse *adresse, int *capital, int *duree, int *cout)
{
    printf("Entrez le nom de la tâche : ");
    while( (scanf("%s", nomTache) != 1 ) )
    {
        printf("Entrez un nom correct, avec maximum 30 caractères.\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le nom de l'entreprise : ");
    while( (scanf("%s", entreprise) != 1 ) )
    {
        printf("Entrez un nom correct, avec maximum 30 caractères.\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez la ville de l'entreprise : ");
    while( (scanf("%s", adresse->ville) != 1 ) )
    {
        printf("Entrez une adresse correct, avec maximum 100 caractères.\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le numéro de rue de l'entreprise : ");
    while( (scanf("%d", &(adresse->numero)) != 1 ) && adresse->numero <= 0 )
    {
        printf("/!/Entrez un numéro de rue correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le nom de la rue de l'entreprise : ");
    while( (scanf("%s", adresse->nomRue) != 1 ) )
    {
        printf("/!/Entrez un nom de rue correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }
    
    printf("Entrez le code postale de l'entreprise : ");
    while( (scanf("%d", &(adresse->codePostal)) != 1 ) && adresse->codePostal <= 0 )
    {
        printf("/!/Entrez un code postale correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le capital de l'entreprise : ");
    while( (scanf("%d", capital) != 1 ) && *capital <= 0 )
    {
        printf("/!/Entrez un capital correct/!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez la durée en jours de la tâche : ");
    while( (scanf("%d", duree) != 1 ) )
    {
        printf("/!/Entrez une durée correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le cout de la tâche : ");
    while( (scanf("%d", cout) != 1 ) )
    {
        printf(" /!/ Entrez un cout correct. /!/\n Entrez ici :");
        while (getchar() != '\n');
    }

}

void ajouterMaillonDevisFin(ListeDevis *liste) 
{
    MaillonDevis *nouveauMaillon = (MaillonDevis*)malloc(sizeof(MaillonDevis));
    
    if (nouveauMaillon == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(-1);
    }

    // Utiliser la fonction de saisie du dessus
    saisieMaillon(nouveauMaillon->devis.nomTache, nouveauMaillon->devis.entreprise, 
                   &(nouveauMaillon->devis.adresse), &(nouveauMaillon->devis.capital),
                   &(nouveauMaillon->devis.duree), &(nouveauMaillon->devis.cout));

    nouveauMaillon->suivant = NULL;

    if (*liste == NULL) 
    {
        *liste = nouveauMaillon;
    }
    else
    {
        MaillonDevis *courant = *liste;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveauMaillon;
    }
}

void ajouterMaillonDevisDebut(ListeDevis *liste)
{
    MaillonDevis *nouveauMaillon = (MaillonDevis*)malloc(sizeof(MaillonDevis));
    
    if (nouveauMaillon == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // Utiliser la fonction de saisie du dessus
    saisieMaillon(nouveauMaillon->devis.nomTache, nouveauMaillon->devis.entreprise, 
                   &(nouveauMaillon->devis.adresse), &(nouveauMaillon->devis.capital),
                   &(nouveauMaillon->devis.duree), &(nouveauMaillon->devis.cout));

    nouveauMaillon->suivant = *liste;

    *liste = nouveauMaillon;
}


//void afficherDevisPourTypeTravaux(MaillonDevis* liste, char* typeTravaux) {
//    MaillonDevis* courant = liste;
//    int trouve = 0;
//
//    while (courant != NULL) {
//        if (strcmp(courant->devis.nomTache, typeTravaux) == 0) {
//            afficherUnDevis(&courant->devis);
//            trouve = 1;
//        }
//        courant = courant->suivant;
//    }
//
//    if (!trouve) {
//        printf("Aucun devis trouvé pour le type de travaux : %s\n", typeTravaux);
//    }
//}
//
//void afficherDevisPourTypeTravauxEtEntreprise(MaillonDevis* liste, char* typeTravaux, char* nomEntreprise) {
//    MaillonDevis* courant = liste;
//    int trouve = 0;
//
//    while (courant != NULL) {
//        if (strcmp(courant->devis.nomTache, typeTravaux) == 0 && strcmp(courant->devis.entreprise, nomEntreprise) == 0) {
//            afficherUnDevis(&courant->devis);
//            trouve = 1;
//        }
//        courant = courant->suivant;
//    }
//
//    if (!trouve) {
//        printf("Aucun devis trouvé pour le type de travaux : %s et l'entreprise : %s\n", typeTravaux, nomEntreprise);
//    }
//}

void supprimerDernierMaillon(ListeDevis *liste) {
    if (*liste == NULL) {
        fprintf(stderr, "Erreur : La liste est vide.\n");
        exit(-1);
    }

    MaillonDevis *courant = *liste;
    MaillonDevis *precedent = NULL;

    // va au bout de la chaine et supprime de dernier
    while (courant->suivant != NULL) {
        precedent = courant;
        courant = courant->suivant;
    }
    free(courant);

    // met NULL le dernier maillon
    if (precedent != NULL) {
        precedent->suivant = NULL;
    } 
    else // sinon y'a qu'un élément donc on le supr et la liste est vide
    { 

        *liste = NULL;
    }
}

