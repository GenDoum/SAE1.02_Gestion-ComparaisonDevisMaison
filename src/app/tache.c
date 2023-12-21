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

ListeDevis creerListeDevisVide(void) {
    return NULL;
}

bool estVide(ListeDevis liste) {
    return liste == NULL;
}

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

void affichDevis( Devis *devis )
{
    printf("Devis de l'entreprise %s\n", devis->entreprise );
    printf("Tâche : %s\n", devis->nomTache);
    printf("Adresse de l'enreprise : %d %s, %s %s \n", devis->adresse.numero, devis->adresse.nomRue, devis->adresse.ville, devis->adresse.codePostal);
    printf("Capital de l'entreprise : %d\n", devis->capital);
    printf("Durée de la tâche : %d jours\n");
    printf("Cout : %d\n", devis->cout);
}

void affichListeDevis( MaillonDevis * maillon )
{
    if ( maillon == NULL )
    {
        printf("La liste est vide.\n");
        return;
    }

    if ( maillon->suivant == NULL )
    {
        affichDevis(maillon->devis);
    }
}

int rechercheDichotomique(Offre* tOffre[], int nbOffre, char* nomTache, int* trouve){
    int debut = 0;
    int fin = nbOffre - 1, milieu;

    while (debut <= fin){
        milieu = (debut + fin) / 2;
        if (strcmp(tOffre[milieu]->travaux, nomTache) == 0){
            *trouve = 1;
            return milieu;
        } else if (strcmp(tOffre[milieu]->travaux, nomTache) < 0){
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }

    *trouve = 0;
    return debut;
}

Devis** chargerFichierDevis(char *nomFic, int *nbDevi, int* max){
    int trouve, pos, i;
    char nomTache[21], char entreprise[21], char ville[101], char nomRue[101];
    int numero, codePostal, capital, duree, cout;
    FILE *fe;

    if ((fe = fopen(nomFic, "r")) == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    nbDevi = 0;
    *max = 10;
    Devis **tDevis, **aux;
    
    if ((tDevis = (Devis**)malloc(*max * sizeof(Devis*))) == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    fscanf(fe, "%s%s%d%s%s%d%d%d%d", nomTache, entreprise, &numero, nomRue, ville, codePostal, &capital, &duree, &cout);
    while(!feof(fe)){
        pos = rechercheDichotomique(tDevis, nbDevi, nomTache, &trouve);
        if (trouve == 0){
            if (*nbDevi == *max){
                *max += 10;
                if ((aux = (Devis**)realloc(tDevis, *max * sizeof(Devis*))) == NULL){
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                tDevis = aux;
            }
            for (i = *nbDevi; i > pos; i--){
                tDevis[i] = tDevis[i - 1];
            }
            if ((tDevis[pos] = (Devis*)malloc(sizeof(Devis))) == NULL){
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(tDevis[pos]->nomTache, nomTache);
            strcpy(tDevis[pos]->entreprise, entreprise);
            strcpy(tDevis[pos]->adresse.ville, ville);
            strcpy(tDevis[pos]->adresse.nomRue, nomRue);
            tDevis[pos]->adresse.numero = numero;
            tDevis[pos]->adresse.codePostal = codePostal;
            tDevis[pos]->capital = capital;
            tDevis[pos]->duree = duree;
            tDevis[pos]->cout = cout;
            (*nbDevi)++;
        }
        fscanf(fe, "%s%s%d%s%s%d%d%d%d", nomTache, entreprise, &numero, nomRue, ville, codePostal, &capital, &duree, &cout);
        fgets(nomTache, 21, fe);
        nomTache[strlen(nomTache) - 1] = '\0';
        ajouterMaillonDevisFin(&tDevis[pos]->listeDevis);
        fscanf(fe, "%s%s%d%s%s%d%d%d%d", nomTache, entreprise, &numero, nomRue, ville, codePostal, &capital, &duree, &cout);
    }
    fclose(fe);
    return tDevis;
}

void afficherDevis(Devis **tDevis, int nbDevis){
    int i;
    for (i = 0; i < nbDevis; i++){
        affichDevis(tDevis[i]);
    }
}