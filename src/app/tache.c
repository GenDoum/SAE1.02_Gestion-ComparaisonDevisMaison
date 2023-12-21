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

// int chargerDevis(Devis d, int* tabDevis[], int maxDevis){

//     int i;
//     FILE* fe;
//     if((fe=fopen("donnee/devis.txt","r"))==NULL){
//         perror("fopen");
//         exit(-1);
//     }

//     i=0;

//     while((fscanf(fe, "%[^\n]\n%[^\n]\n%d, %49[^-] - %d - %49[^\n]\n%d\n%d\n%d\n", d.nomTache, d.entreprise, &d.adresse.numero, d.adresse.nomRue, &d.adresse.ville, d.adresse.codePostal, &d.capital, &d.duree, &d.cout))==9){ //tant que le scan des 9 éléments se fait
//         if(i>maxDevis){
//             tabDevis = (Offre *)realloc(tabDevis,sizeof(tabDevis)+1);
//             ++maxDevis;
//         }
//         tabDevis[i]=d;
//         printf("devis chargé (tableau):\n tache %s\n nom %s\n numero %d\n rue %s\n cp %d\n ville %s\n capital %d\n dure %d\n cout %d\n",tabDevis[i].tache, tabDevis[i].nom, tabDevis[i].adress.numero, tabDevis[i].adress.rue, tabDevis[i].adress.cp, tabDevis[i].adress.ville, tabDevis[i].capital, tabDevis[i].dure, tabDevis[i].coutTache); //vérification en affichant la ligne du tableau
//         i++; 
//         puts("");
//     }
// }

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
    while( (scanf("%d", adresse->numero) != 1 ) )
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
    while( (scanf("%d", adresse->codePostal) != 1 ) )
    {
        printf("/!/Entrez un code postale correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le capital de l'entreprise : ");
    while( (scanf("%d", capital) != 1 ) )
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
